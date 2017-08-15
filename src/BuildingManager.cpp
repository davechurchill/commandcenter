#include "Common.h"
#include "BuildingManager.h"
#include "Micro.h"
#include "CCBot.h"
#include "Util.h"

BuildingManager::BuildingManager(CCBot & bot)
    : m_bot(bot)
    , m_buildingPlacer(bot)
    , m_debugMode(false)
    , m_reservedMinerals(0)
    , m_reservedGas(0)
{

}

void BuildingManager::onStart()
{
    m_buildingPlacer.onStart();
}

// gets called every frame from GameCommander
void BuildingManager::onFrame()
{
    for (auto & unit : m_bot.UnitInfo().getUnits(Players::Self))
    {
        // filter out units which aren't buildings under construction
        if (m_bot.Data(unit.unit_type).isBuilding)
        {
            std::stringstream ss;
            ss << unit.tag;
            m_bot.Map().drawText(unit.pos, ss.str());
        }
    }

    validateWorkersAndBuildings();          // check to see if assigned workers have died en route or while constructing
    assignWorkersToUnassignedBuildings();   // assign workers to the unassigned buildings and label them 'planned'    
    constructAssignedBuildings();           // for each planned building, if the worker isn't constructing, send the command    
    checkForStartedConstruction();          // check to see if any buildings have started construction and update data structures    
    checkForDeadTerranBuilders();           // if we are terran and a building is under construction without a worker, assign a new one    
    checkForCompletedBuildings();           // check to see if any buildings have completed and update data structures

    drawBuildingInformation();
}

bool BuildingManager::isBeingBuilt(sc2::UnitTypeID type)
{
    for (auto & b : m_buildings)
    {
        if (b.type == type)
        {
            return true;
        }
    }

    return false;
}

// STEP 1: DO BOOK KEEPING ON WORKERS WHICH MAY HAVE DIED
void BuildingManager::validateWorkersAndBuildings()
{
    // TODO: if a terran worker dies while constructing and its building
    //       is under construction, place unit back into buildingsNeedingBuilders

    std::vector<Building> toRemove;

    // find any buildings which have become obsolete
    for (auto & b : m_buildings)
    {
        if (b.status != BuildingStatus::UnderConstruction)
        {
            continue;
        }

        auto buildingUnit = m_bot.GetUnit(b.buildingUnitTag);

        // TODO: || !b.buildingUnit->getType().isBuilding()
        if (!buildingUnit || (buildingUnit->health <= 0))
        {
            toRemove.push_back(b);
        }
    }

    removeBuildings(toRemove);
}

// STEP 2: ASSIGN WORKERS TO BUILDINGS WITHOUT THEM
void BuildingManager::assignWorkersToUnassignedBuildings()
{
    // for each building that doesn't have a builder, assign one
    for (Building & b : m_buildings)
    {
        if (b.status != BuildingStatus::Unassigned)
        {
            continue;
        }

        BOT_ASSERT(b.builderUnitTag == 0, "Error: Tried to assign a builder to a building that already had one ");

        if (m_debugMode) { printf("Assigning Worker To: %s", sc2::UnitTypeToName(b.type)); }

        // grab a worker unit from WorkerManager which is closest to this final position
        sc2::Point2D testLocation = getBuildingLocation(b);
        if (!m_bot.Map().isValid(testLocation))
        {
            continue;
        }

        b.finalPosition = testLocation;

        // grab the worker unit from WorkerManager which is closest to this final position
        UnitTag builderUnitTag = m_bot.Workers().getBuilder(b);
        b.builderUnitTag = builderUnitTag;
        if (!b.builderUnitTag)
        {
            continue;
        }

        // reserve this building's space
        m_buildingPlacer.reserveTiles((int)b.finalPosition.x, (int)b.finalPosition.y, Util::GetUnitTypeWidth(b.type, m_bot), Util::GetUnitTypeHeight(b.type, m_bot));

        b.status = BuildingStatus::Assigned;
    }
}

// STEP 3: ISSUE CONSTRUCTION ORDERS TO ASSIGN BUILDINGS AS NEEDED
void BuildingManager::constructAssignedBuildings()
{
    for (auto & b : m_buildings)
    {
        if (b.status != BuildingStatus::Assigned)
        {
            continue;
        }

        // TODO: not sure if this is the correct way to tell if the building is constructing
        sc2::AbilityID buildAbility = m_bot.Data(b.type).buildAbility;
        const sc2::Unit * builderUnit = m_bot.GetUnit(b.builderUnitTag);

        bool isConstructing = false;

        // if we're zerg and the builder unit is null, we assume it morphed into the building
        if (m_bot.GetPlayerRace(Players::Self) == sc2::Race::Zerg)
        {
            if (!builderUnit)
            {
                isConstructing = true;
            }
        }
        else
        {
            BOT_ASSERT(builderUnit, "null builder unit");
            isConstructing = (builderUnit->orders.size() > 0) && (builderUnit->orders[0].ability_id == buildAbility);
        }

        // if that worker is not currently constructing
        if (!isConstructing)
        {
            // if we haven't explored the build position, go there
            if (!isBuildingPositionExplored(b))
            {
                Micro::SmartMove(*builderUnit, b.finalPosition, m_bot);
            }
            // if this is not the first time we've sent this guy to build this
            // it must be the case that something was in the way of building
            else if (b.buildCommandGiven)
            {
                // TODO: in here is where we would check to see if the builder died on the way
                //       or if things are taking too long, or the build location is no longer valid
            }
            else
            {
                // if it's a refinery, the build command has to be on the geyser unit tag
                if (Util::IsRefineryType(b.type))
                {
                    // first we find the geyser at the desired location
                    UnitTag geyserTag = 0;
                    for (auto & unit : m_bot.Observation()->GetUnits())
                    {
                        if (Util::IsGeyser(unit) && Util::Dist(b.finalPosition, unit.pos) < 3)
                        {
                            geyserTag = unit.tag;
                            break;
                        }
                    }

                    if (geyserTag)
                    {
                        Micro::SmartBuildTag(b.builderUnitTag, b.type, geyserTag, m_bot);
                    }
                    else
                    {
                        std::cout << "WARNING: NO VALID GEYSER UNIT FOUND TO BUILD ON, SKIPPING REFINERY\n";
                    }
                }
                // if it's not a refinery, we build right on the position
                else
                {
                    Micro::SmartBuild(b.builderUnitTag, b.type, b.finalPosition, m_bot);
                }

                // set the flag to true
                b.buildCommandGiven = true;
            }
        }
    }
}

// STEP 4: UPDATE DATA STRUCTURES FOR BUILDINGS STARTING CONSTRUCTION
void BuildingManager::checkForStartedConstruction()
{
    // for each building unit which is being constructed
    for (auto & buildingStarted : m_bot.UnitInfo().getUnits(Players::Self))
    {
        // filter out units which aren't buildings under construction
        if (!m_bot.Data(buildingStarted.unit_type).isBuilding || buildingStarted.build_progress == 0.0f || buildingStarted.build_progress == 1.0f)
        {
            continue;
        }

        // check all our building status objects to see if we have a match and if we do, update it

        for (auto & b : m_buildings)
        {
            if (b.status != BuildingStatus::Assigned)
            {
                continue;
            }

            // check if the positions match
            float dx = b.finalPosition.x - buildingStarted.pos.x;
            float dy = b.finalPosition.y - buildingStarted.pos.y;

            if (dx*dx + dy*dy < 1)
            {
                if (b.buildingUnitTag != 0)
                {
                    std::cout << "Building mis-match somehow\n";
                }

                // the resources should now be spent, so unreserve them
                m_reservedMinerals -= Util::GetUnitTypeMineralPrice(buildingStarted.unit_type, m_bot);
                m_reservedGas      -= Util::GetUnitTypeGasPrice(buildingStarted.unit_type, m_bot);
                
                // flag it as started and set the buildingUnit
                b.underConstruction = true;
                b.buildingUnitTag = buildingStarted.tag;

                // if we are zerg, the buildingUnit now becomes nullptr since it's destroyed
                if (m_bot.GetPlayerRace(Players::Self) == sc2::Race::Zerg)
                {
                    b.builderUnitTag = 0;
                }
                else if (m_bot.GetPlayerRace(Players::Self) == sc2::Race::Protoss)
                {
                    m_bot.Workers().finishedWithWorker(b.builderUnitTag);
                    b.builderUnitTag = 0;
                }

                // put it in the under construction vector
                b.status = BuildingStatus::UnderConstruction;

                // free this space
                m_buildingPlacer.freeTiles((int)b.finalPosition.x, (int)b.finalPosition.y, Util::GetUnitTypeWidth(b.type, m_bot), Util::GetUnitTypeHeight(b.type, m_bot));

                // only one building will match
                break;
            }
        }
    }
}

// STEP 5: IF WE ARE TERRAN, THIS MATTERS, SO: LOL
void BuildingManager::checkForDeadTerranBuilders() {}

// STEP 6: CHECK FOR COMPLETED BUILDINGS
void BuildingManager::checkForCompletedBuildings()
{
    std::vector<Building> toRemove;

    // for each of our buildings under construction
    for (auto & b : m_buildings)
    {
        if (b.status != BuildingStatus::UnderConstruction)
        {
            continue;
        }

        // if the unit has completed
        if (m_bot.GetUnit(b.buildingUnitTag)->build_progress == 1.0f)
        {
            // if we are terran, give the worker back to worker manager
            if (m_bot.GetPlayerRace(Players::Self) == sc2::Race::Terran)
            {
                m_bot.Workers().finishedWithWorker(b.builderUnitTag);
            }

            // remove this unit from the under construction vector
            toRemove.push_back(b);
        }
    }

    removeBuildings(toRemove);
}

// add a new building to be constructed
void BuildingManager::addBuildingTask(const sc2::UnitTypeID & type, const sc2::Point2D & desiredPosition)
{
    m_reservedMinerals  += Util::GetUnitTypeMineralPrice(type, m_bot);
    m_reservedGas	    += Util::GetUnitTypeGasPrice(type, m_bot);

    Building b(type, desiredPosition);
    b.status = BuildingStatus::Unassigned;

    m_buildings.push_back(b);
}

// TODO: may need to iterate over all tiles of the building footprint
bool BuildingManager::isBuildingPositionExplored(const Building & b) const
{
    return m_bot.Map().isExplored(b.finalPosition);
}


char BuildingManager::getBuildingWorkerCode(const Building & b) const
{
    return b.builderUnitTag == 0 ? 'X' : 'W';
}

int BuildingManager::getReservedMinerals()
{
    return m_reservedMinerals;
}

int BuildingManager::getReservedGas()
{
    return m_reservedGas;
}

void BuildingManager::drawBuildingInformation()
{
    m_buildingPlacer.drawReservedTiles();

    if (!m_bot.Config().DrawBuildingInfo)
    {
        return;
    }

    std::stringstream ss;
    ss << "Building Information " << m_buildings.size() << "\n\n\n";

    int yspace = 0;

    for (const auto & b : m_buildings)
    {
        std::stringstream dss;

        if (b.builderUnitTag)
        {
            dss << "\n\nBuilder: " << b.builderUnitTag << "\n";
        }

        if (b.buildingUnitTag)
        {
            dss << "Building: " << b.buildingUnitTag << "\n" << m_bot.GetUnit(b.buildingUnitTag)->build_progress;
            m_bot.Map().drawText(m_bot.GetUnit(b.buildingUnitTag)->pos, dss.str());
        }



        if (b.status == BuildingStatus::Unassigned)
        {
            ss << "Unassigned " << sc2::UnitTypeToName(b.type) << "    " << getBuildingWorkerCode(b) << "\n";
        }
        else if (b.status == BuildingStatus::Assigned)
        {
            ss << "Assigned " << sc2::UnitTypeToName(b.type) << "    " << b.builderUnitTag << " " << getBuildingWorkerCode(b) << " (" << b.finalPosition.x << "," << b.finalPosition.y << ")\n";

            float x1 = b.finalPosition.x;
            float y1 = b.finalPosition.y;
            float x2 = b.finalPosition.x + Util::GetUnitTypeWidth(b.type, m_bot);
            float y2 = b.finalPosition.y + Util::GetUnitTypeHeight(b.type, m_bot);

            m_bot.Map().drawSquare(x1, y1, x2, y2, sc2::Colors::Red);
            //m_bot.Map().drawLine(b.finalPosition, m_bot.GetUnit(b.builderUnitTag)->pos, sc2::Colors::Yellow);
        }
        else if (b.status == BuildingStatus::UnderConstruction)
        {
            ss << "Constructing " << sc2::UnitTypeToName(b.type) << "    " << b.builderUnitTag << " " << b.buildingUnitTag << " " << getBuildingWorkerCode(b) << "\n";
        }
    }

    m_bot.Map().drawTextScreen(sc2::Point2D(0.05f, 0.05f), ss.str());
}

std::vector<sc2::UnitTypeID> BuildingManager::buildingsQueued() const
{
    std::vector<sc2::UnitTypeID> buildingsQueued;

    for (const auto & b : m_buildings)
    {
        if (b.status == BuildingStatus::Unassigned || b.status == BuildingStatus::Assigned)
        {
            buildingsQueued.push_back(b.type);
        }
    }

    return buildingsQueued;
}

sc2::Point2D BuildingManager::getBuildingLocation(const Building & b)
{
    size_t numPylons = m_bot.UnitInfo().getUnitTypeCount(Players::Self, Util::GetSupplyProvider(m_bot.GetPlayerRace(Players::Self)), true);

    // TODO: if requires psi and we have no pylons return 0

    if (Util::IsRefineryType(b.type))
    {
        return m_buildingPlacer.getRefineryPosition();
    }

    if (Util::IsTownHallType(b.type))
    {
        // TODO: fix this so we can actually expand
        //return m_bot.Bases().getNextExpansion(Players::Self);
    }

    // get a position within our region
    // TODO: put back in special pylon / cannon spacing
    return m_buildingPlacer.getBuildLocationNear(b, m_bot.Config().BuildingSpacing);
}

void BuildingManager::removeBuildings(const std::vector<Building> & toRemove)
{
    for (auto & b : toRemove)
    {
        const auto & it = std::find(m_buildings.begin(), m_buildings.end(), b);

        if (it != m_buildings.end())
        {
            m_buildings.erase(it);
        }
    }
}