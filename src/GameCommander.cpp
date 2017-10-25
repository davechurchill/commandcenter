#include "GameCommander.h"
#include "CCBot.h"
#include "Util.h"

GameCommander::GameCommander(CCBot & bot)
    : m_bot                 (bot)
    , m_productionManager   (bot)
    , m_scoutManager        (bot)
    , m_combatCommander     (bot)
    , m_initialScoutSet     (false)
{

}

void GameCommander::onStart()
{
    m_productionManager.onStart();
    m_scoutManager.onStart();
    m_combatCommander.onStart();
}

void GameCommander::onFrame()
{
    m_timer.start();

    handleUnitAssignments();

    m_productionManager.onFrame();
    m_scoutManager.onFrame();
    m_combatCommander.onFrame(m_combatUnits);

    drawDebugInterface();
}

void GameCommander::drawDebugInterface()
{
    drawGameInformation(4, 1);
}

void GameCommander::drawGameInformation(int x, int y)
{
    std::stringstream ss;
    ss << "Players: " << "\n";
    ss << "Strategy: " << m_bot.Config().StrategyName << "\n";
    ss << "Map Name: " << "\n";
    ss << "Time: " << "\n";
}

// assigns units to various managers
void GameCommander::handleUnitAssignments()
{
    m_validUnits.clear();
    m_combatUnits.clear();

    // filter our units for those which are valid and usable
    setValidUnits();

    // set each type of unit
    setScoutUnits();
    setCombatUnits();
}

bool GameCommander::isAssigned(const Unit & unit) const
{
    return     (std::find(m_combatUnits.begin(), m_combatUnits.end(), unit) != m_combatUnits.end())
        || (std::find(m_scoutUnits.begin(), m_scoutUnits.end(), unit) != m_scoutUnits.end());
}

// validates units as usable for distribution to various managers
void GameCommander::setValidUnits()
{
    // make sure the unit is completed and alive and usable
    for (auto & unit : m_bot.UnitInfo().getUnits(Players::Self))
    {
        m_validUnits.push_back(unit);
    }
}

void GameCommander::setScoutUnits()
{
    // if we haven't set a scout unit, do it
    if (m_scoutUnits.empty() && !m_initialScoutSet)
    {
        // if it exists
        if (shouldSendInitialScout())
        {
            // grab the closest worker to the supply provider to send to scout
            Unit workerScout = m_bot.Workers().getClosestMineralWorkerTo(m_bot.GetStartLocation());

            // if we find a worker (which we should) add it to the scout units
            if (workerScout.isValid())
            {
                m_scoutManager.setWorkerScout(workerScout);
                assignUnit(workerScout, m_scoutUnits);
                m_initialScoutSet = true;
            }
            else
            {
                
            }
        }
    }
}

bool GameCommander::shouldSendInitialScout()
{
#ifdef SC2API
    switch (m_bot.GetPlayerRace(Players::Self))
    {
        case sc2::Race::Terran:  return m_bot.UnitInfo().getUnitTypeCount(Players::Self, UnitType(sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT, m_bot), true) > 0;
        case sc2::Race::Protoss: return m_bot.UnitInfo().getUnitTypeCount(Players::Self, UnitType(sc2::UNIT_TYPEID::PROTOSS_PYLON, m_bot), true) > 0;
        case sc2::Race::Zerg:    return m_bot.UnitInfo().getUnitTypeCount(Players::Self, UnitType(sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL, m_bot), true) > 0;
        default: return false;
    }
#else
    if (m_bot.GetPlayerRace(Players::Self) == BWAPI::Races::Zerg)
    {
        return m_bot.UnitInfo().getUnitTypeCount(Players::Self, UnitType(BWAPI::UnitTypes::Zerg_Spawning_Pool, m_bot), true) > 0;
    }
    else
    {
        return m_bot.UnitInfo().getUnitTypeCount(Players::Self, UnitType(m_bot.GetPlayerRace(Players::Self).getSupplyProvider(), m_bot), true) > 0;
    }
#endif
}

// sets combat units to be passed to CombatCommander
void GameCommander::setCombatUnits()
{
    for (auto & unit : m_validUnits)
    {
        BOT_ASSERT(unit.isValid(), "Have a null unit in our valid units\n");

        if (!isAssigned(unit) && unit.getType().isCombatUnit())
        {
            assignUnit(unit, m_combatUnits);
        }
    }
}

void GameCommander::onUnitCreate(const Unit & unit)
{

}

void GameCommander::onUnitDestroy(const Unit & unit)
{
    //_productionManager.onUnitDestroy(unit);
}


void GameCommander::assignUnit(const Unit & unit, std::vector<Unit> & units)
{
    if (std::find(m_scoutUnits.begin(), m_scoutUnits.end(), unit) != m_scoutUnits.end())
    {
        m_scoutUnits.erase(std::remove(m_scoutUnits.begin(), m_scoutUnits.end(), unit), m_scoutUnits.end());
    }
    else if (std::find(m_combatUnits.begin(), m_combatUnits.end(), unit) != m_combatUnits.end())
    {
        m_combatUnits.erase(std::remove(m_combatUnits.begin(), m_combatUnits.end(), unit), m_combatUnits.end());
    }

    units.push_back(unit);
}
