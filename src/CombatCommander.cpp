#include "CombatCommander.h"
#include "Util.h"
#include "CCBot.h"
#include "Micro.h"

const size_t IdlePriority = 0;
const size_t AttackPriority = 1;
const size_t BaseDefensePriority = 2;
const size_t ScoutDefensePriority = 3;
const size_t DropPriority = 4;

CombatCommander::CombatCommander(CCBot & bot)
    : m_bot(bot)
    , m_squadData(bot)
    , m_initialized(false)
    , m_attackStarted(false)
{

}

void CombatCommander::onStart()
{
    m_squadData.clearSquadData();

    SquadOrder idleOrder(SquadOrderTypes::Idle, m_bot.GetStartLocation(), 5, "Chill Out");
    m_squadData.addSquad("Idle", Squad("Idle", idleOrder, IdlePriority, m_bot));

    // the main attack squad that will pressure the enemy's closest base location
    SquadOrder mainAttackOrder(SquadOrderTypes::Attack, sc2::Point2D(0.0f, 0.0f), 25, "Attack Enemy Base");
    m_squadData.addSquad("MainAttack", Squad("MainAttack", mainAttackOrder, AttackPriority, m_bot));

    // the scout defense squad will handle chasing the enemy worker scout
    SquadOrder enemyScoutDefense(SquadOrderTypes::Defend, m_bot.GetStartLocation(), 25, "Get the scout");
    m_squadData.addSquad("ScoutDefense", Squad("ScoutDefense", enemyScoutDefense, ScoutDefensePriority, m_bot));
}

bool CombatCommander::isSquadUpdateFrame()
{
    return true;
}

void CombatCommander::onFrame(const std::vector<UnitTag> & combatUnits)
{
    if (!m_attackStarted)
    {
        m_attackStarted = shouldWeStartAttacking();
    }

    m_combatUnits = combatUnits;

    if (isSquadUpdateFrame())
    {
        updateIdleSquad();
        updateScoutDefenseSquad();
        updateDefenseSquads();
        updateAttackSquads();
    }

    m_squadData.onFrame();
}

bool CombatCommander::shouldWeStartAttacking()
{
    // TODO: make this more clever
    // For now: start attacking when we have more than 10 combat units
    return m_combatUnits.size() >= m_bot.Config().CombatUnitsForAttack;
}

void CombatCommander::updateIdleSquad()
{
    Squad & idleSquad = m_squadData.getSquad("Idle");
    for (auto & unit : m_combatUnits)
    {
        // if it hasn't been assigned to a squad yet, put it in the low priority idle squad
        if (m_squadData.canAssignUnitToSquad(unit, idleSquad))
        {
            idleSquad.addUnit(unit);
        }
    }
}

void CombatCommander::updateAttackSquads()
{
    if (!m_attackStarted)
    {
        return;
    }

    Squad & mainAttackSquad = m_squadData.getSquad("MainAttack");

    for (auto & unitTag : m_combatUnits)
    {
        auto unit = m_bot.GetUnit(unitTag);
        BOT_ASSERT(unit, "null unit in combat units");

        // get every unit of a lower priority and put it into the attack squad
        if (!Util::IsWorker(*unit) 
            && !(unit->unit_type == sc2::UNIT_TYPEID::ZERG_OVERLORD) 
            && !(unit->unit_type == sc2::UNIT_TYPEID::ZERG_QUEEN) 
            && m_squadData.canAssignUnitToSquad(unitTag, mainAttackSquad))
        {
            m_squadData.assignUnitToSquad(unitTag, mainAttackSquad);
        }
    }

    SquadOrder mainAttackOrder(SquadOrderTypes::Attack, getMainAttackLocation(), 25, "Attack Enemy Base");
    mainAttackSquad.setSquadOrder(mainAttackOrder);
}

void CombatCommander::updateScoutDefenseSquad()
{
    if (m_combatUnits.empty())
    {
        return;
    }

    // if the current squad has units in it then we can ignore this
    Squad & scoutDefenseSquad = m_squadData.getSquad("ScoutDefense");

    // get the region that our base is located in
    const BaseLocation * myBaseLocation = m_bot.Bases().getPlayerStartingBaseLocation(Players::Self);
    BOT_ASSERT(myBaseLocation, "null self base location");

    // get all of the enemy units in this region
    std::vector<UnitTag> enemyUnitsInRegion;
    for (auto & unit : m_bot.UnitInfo().getUnits(Players::Enemy))
    {
        if (myBaseLocation->containsPosition(unit.pos))
        {
            enemyUnitsInRegion.push_back(unit);
        }
    }

    // if there's an enemy worker in our region then assign someone to chase him
    bool assignScoutDefender = (enemyUnitsInRegion.size() == 1) && Util::IsWorker(*m_bot.GetUnit(enemyUnitsInRegion[0]));

    // if our current squad is empty and we should assign a worker, do it
    if (scoutDefenseSquad.isEmpty() && assignScoutDefender)
    {
        // the enemy worker that is attacking us
        UnitTag enemyWorkerTag = *enemyUnitsInRegion.begin();
        auto enemyWorkerUnit = m_bot.GetUnit(enemyWorkerTag);
        BOT_ASSERT(enemyWorkerUnit, "null enemy worker unit");

        // get our worker unit that is mining that is closest to it
        UnitTag workerDefenderTag = findClosestWorkerTo(m_combatUnits, enemyWorkerUnit->pos);

        if (enemyWorkerTag && workerDefenderTag)
        {
            // grab it from the worker manager and put it in the squad
            if (m_squadData.canAssignUnitToSquad(workerDefenderTag, scoutDefenseSquad))
            {
                m_bot.Workers().setCombatWorker(workerDefenderTag);
                m_squadData.assignUnitToSquad(workerDefenderTag, scoutDefenseSquad);
            }
        }
    }
    // if our squad is not empty and we shouldn't have a worker chasing then take him out of the squad
    else if (!scoutDefenseSquad.isEmpty() && !assignScoutDefender)
    {
        for (auto & unitTag : scoutDefenseSquad.getUnits())
        {
            auto unit = m_bot.GetUnit(unitTag);
            BOT_ASSERT(unit, "null unit in scoutDefenseSquad");

            Micro::SmartStop(unitTag, m_bot);
            if (Util::IsWorker(*unit))
            {
                m_bot.Workers().finishedWithWorker(unitTag);
            }
        }

        scoutDefenseSquad.clear();
    }
}

void CombatCommander::updateDefenseSquads()
{
    if (m_combatUnits.empty())
    {
        return;
    }

    // for each of our occupied regions
    const BaseLocation * enemyBaseLocation = m_bot.Bases().getPlayerStartingBaseLocation(Players::Enemy);
    for (const BaseLocation * myBaseLocation : m_bot.Bases().getOccupiedBaseLocations(Players::Self))
    {
        // don't defend inside the enemy region, this will end badly when we are stealing gas or cannon rushing
        if (myBaseLocation == enemyBaseLocation)
        {
            continue;
        }

        sc2::Point2D basePosition = myBaseLocation->getPosition();

        // start off assuming all enemy units in region are just workers
        int numDefendersPerEnemyUnit = 2;

        // all of the enemy units in this region
        std::vector<UnitTag> enemyUnitsInRegion;
        for (auto & unit : m_bot.UnitInfo().getUnits(Players::Enemy))
        {
            // if it's an overlord, don't worry about it for defense, we don't care what they see
            if (unit.unit_type == sc2::UNIT_TYPEID::ZERG_OVERLORD)
            {
                continue;
            }

            if (myBaseLocation->containsPosition(unit.pos))
            {
                enemyUnitsInRegion.push_back(unit.tag);
            }
        }

        // we can ignore the first enemy worker in our region since we assume it is a scout
        for (auto & unitTag : enemyUnitsInRegion)
        {
            auto unit = m_bot.GetUnit(unitTag);
            BOT_ASSERT(unit, "null enemyt unit in region");

            if (Util::IsWorker(*unit))
            {
                enemyUnitsInRegion.erase(std::remove(enemyUnitsInRegion.begin(), enemyUnitsInRegion.end(), unitTag), enemyUnitsInRegion.end());
                break;
            }
        }

        // calculate how many units are flying / ground units
        int numEnemyFlyingInRegion = 0;
        int numEnemyGroundInRegion = 0;
        for (auto & unitTag : enemyUnitsInRegion)
        {
            auto unit = m_bot.GetUnit(unitTag);
            BOT_ASSERT(unit, "null enemyt unit in region");

            if (unit->is_flying)
            {
                numEnemyFlyingInRegion++;
            }
            else
            {
                numEnemyGroundInRegion++;
            }
        }


        std::stringstream squadName;
        squadName << "Base Defense " << basePosition.x << " " << basePosition.y;

        // if there's nothing in this region to worry about
        if (enemyUnitsInRegion.empty())
        {
            // if a defense squad for this region exists, remove it
            if (m_squadData.squadExists(squadName.str()))
            {
                m_squadData.getSquad(squadName.str()).clear();
            }

            // and return, nothing to defend here
            continue;
        }
        else
        {
            // if we don't have a squad assigned to this region already, create one
            if (!m_squadData.squadExists(squadName.str()))
            {
                SquadOrder defendRegion(SquadOrderTypes::Defend, basePosition, 32 * 25, "Defend Region!");
                m_squadData.addSquad(squadName.str(), Squad(squadName.str(), defendRegion, BaseDefensePriority, m_bot));
            }
        }

        // assign units to the squad
        if (m_squadData.squadExists(squadName.str()))
        {
            Squad & defenseSquad = m_squadData.getSquad(squadName.str());

            // figure out how many units we need on defense
            int flyingDefendersNeeded = numDefendersPerEnemyUnit * numEnemyFlyingInRegion;
            int groundDefensersNeeded = numDefendersPerEnemyUnit * numEnemyGroundInRegion;

            updateDefenseSquadUnits(defenseSquad, flyingDefendersNeeded, groundDefensersNeeded);
        }
        else
        {
            BOT_ASSERT(false, "Squad should have existed: %s", squadName.str().c_str());
        }
    }

    // for each of our defense squads, if there aren't any enemy units near the position, remove the squad
    std::set<std::string> uselessDefenseSquads;
    for (const auto & kv : m_squadData.getSquads())
    {
        const Squad & squad = kv.second;
        const SquadOrder & order = squad.getSquadOrder();

        if (order.getType() != SquadOrderTypes::Defend)
        {
            continue;
        }

        bool enemyUnitInRange = false;
        for (auto & unit : m_bot.UnitInfo().getUnits(Players::Enemy))
        {
            if (Util::Dist(unit.pos, order.getPosition()) < order.getRadius())
            {
                enemyUnitInRange = true;
                break;
            }
        }

        if (!enemyUnitInRange)
        {
            m_squadData.getSquad(squad.getName()).clear();
        }
    }
}

void CombatCommander::updateDefenseSquadUnits(Squad & defenseSquad, const size_t & flyingDefendersNeeded, const size_t & groundDefendersNeeded)
{
    auto & squadUnits = defenseSquad.getUnits();

    // TODO: right now this will assign arbitrary defenders, change this so that we make sure they can attack air/ground

    // if there's nothing left to defend, clear the squad
    if (flyingDefendersNeeded == 0 && groundDefendersNeeded == 0)
    {
        defenseSquad.clear();
        return;
    }

    size_t defendersNeeded = flyingDefendersNeeded + groundDefendersNeeded;
    size_t defendersAdded = 0;

    while (defendersNeeded > defendersAdded)
    {
        UnitTag defenderToAdd = findClosestDefender(defenseSquad, defenseSquad.getSquadOrder().getPosition());

        if (defenderToAdd)
        {
            m_squadData.assignUnitToSquad(defenderToAdd, defenseSquad);
            defendersAdded++;
        }
        else
        {
            break;
        }
    }
}

UnitTag CombatCommander::findClosestDefender(const Squad & defenseSquad, const sc2::Point2D & pos)
{
    UnitTag closestDefender = 0;
    float minDistance = std::numeric_limits<float>::max();

    // TODO: add back special case of zergling rush defense

    for (auto & unitTag : m_combatUnits)
    {
        auto unit = m_bot.GetUnit(unitTag);
        BOT_ASSERT(unit, "null combat unit");

        if (!m_squadData.canAssignUnitToSquad(unitTag, defenseSquad))
        {
            continue;
        }

        float dist = Util::Dist(unit->pos, pos);
        if (!closestDefender || (dist < minDistance))
        {
            closestDefender = unitTag;
            minDistance = dist;
        }
    }

    return closestDefender;
}


void CombatCommander::drawSquadInformation()
{
    m_squadData.drawSquadInformation();
}

sc2::Point2D CombatCommander::getMainAttackLocation()
{
    const BaseLocation * enemyBaseLocation = m_bot.Bases().getPlayerStartingBaseLocation(Players::Enemy);

    // First choice: Attack an enemy region if we can see units inside it
    if (enemyBaseLocation)
    {
        sc2::Point2D enemyBasePosition = enemyBaseLocation->getPosition();

        // If the enemy base hasn't been seen yet, go there.
        if (!m_bot.Map().isExplored(enemyBasePosition))
        {
            return enemyBasePosition;
        }
        else
        {
            // if it has been explored, go there if there are any visible enemy units there
            for (auto & enemyUnit : m_bot.UnitInfo().getUnits(Players::Enemy))
            {
                if (Util::Dist(enemyUnit.pos, enemyBasePosition) < 25)
                {
                    return enemyBasePosition;
                }
            }
        }
    }

    // Second choice: Attack known enemy buildings
    for (const auto & kv : m_bot.UnitInfo().getUnitInfoMap(Players::Enemy))
    {
        const UnitInfo & ui = kv.second;

        if (m_bot.Data(ui.type).isBuilding && !(ui.lastPosition.x == 0.0f && ui.lastPosition.y == 0.0f))
        {
            return ui.lastPosition;
        }
    }

    // Third choice: Attack visible enemy units that aren't overlords
    for (auto & enemyUnit : m_bot.UnitInfo().getUnits(Players::Enemy))
    {
        if (enemyUnit.unit_type != sc2::UNIT_TYPEID::ZERG_OVERLORD)
        {
            return enemyUnit.pos;
        }
    }

    // Fourth choice: We can't see anything so explore the map attacking along the way
    return m_bot.Map().getLeastRecentlySeenPosition();
}

UnitTag CombatCommander::findClosestWorkerTo(std::vector<UnitTag> & unitsToAssign, const sc2::Point2D & target)
{
    UnitTag closestMineralWorker = 0;
    float closestDist = std::numeric_limits<float>::max();

    // for each of our workers
    for (auto & unitTag : unitsToAssign)
    {
        auto unit = m_bot.GetUnit(unitTag);
        BOT_ASSERT(unit, "unit to assign was null");

        if (!Util::IsWorker(*unit))
        {
            continue;
        }

        // if it is a move worker
        if (m_bot.Workers().isFree(*unit))
        {
            float dist = Util::Dist(unit->pos, target);

            if (dist < closestDist)
            {
                closestMineralWorker = unitTag;
                dist = closestDist;
            }
        }
    }

    return closestMineralWorker;
}
