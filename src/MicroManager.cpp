#include "MicroManager.h"
#include "CCBot.h"
#include "Util.h"

MicroManager::MicroManager(CCBot & bot)
    : m_bot(bot)
{
}

void MicroManager::setUnits(const std::vector<Unit> & u)
{
    m_units = u;
}

void MicroManager::execute(const SquadOrder & inputOrder)
{
    // Nothing to do if we have no units
    if (m_units.empty() || !(inputOrder.getType() == SquadOrderTypes::Attack || inputOrder.getType() == SquadOrderTypes::Defend))
    {
        return;
    }

    order = inputOrder;

    // Discover enemies within region of interest
    std::set<Unit> nearbyEnemies;

    // if the order is to defend, we only care about units in the radius of the defense
    if (order.getType() == SquadOrderTypes::Defend)
    {
        for (auto & enemyUnit : m_bot.UnitInfo().getUnits(Players::Enemy))
        {
            if (Util::Dist(enemyUnit, order.getPosition()) < order.getRadius())
            {
                nearbyEnemies.insert(enemyUnit);
            }
        }

    } // otherwise we want to see everything on the way as well
    else if (order.getType() == SquadOrderTypes::Attack)
    {
        for (auto & enemyUnit : m_bot.UnitInfo().getUnits(Players::Enemy))
        {
            if (Util::Dist(enemyUnit, order.getPosition()) < order.getRadius())
            {
                nearbyEnemies.insert(enemyUnit);
            }
        }

        for (auto unit : m_units)
        {
            BOT_ASSERT(unit.isValid(), "null unit in attack");

            for (auto & enemyUnit : m_bot.UnitInfo().getUnits(Players::Enemy))
            {
                if (Util::Dist(enemyUnit, unit) < order.getRadius())
                {
                    nearbyEnemies.insert(enemyUnit);
                }
            }
        }
    }

    std::vector<Unit> targetUnitTags;
    std::copy(nearbyEnemies.begin(), nearbyEnemies.end(), std::back_inserter(targetUnitTags));

    // the following block of code attacks all units on the way to the order position
    // we want to do this if the order is attack, defend, or harass
    if (order.getType() == SquadOrderTypes::Attack || order.getType() == SquadOrderTypes::Defend)
    {
        // if this is a defense squad then we care about all units in the area
        if (order.getType() == SquadOrderTypes::Defend)
        {
            executeMicro(targetUnitTags);
        }
        // otherwise we only care about workers if they are in their own region
        // this is because their scout can run around and drag our units around the map
        else
        {
            // if this is the an attack squad
            std::vector<Unit> workersRemoved;
            for (auto & enemyUnit : targetUnitTags)
            {
                BOT_ASSERT(enemyUnit.isValid(), "null enemy unit target");

                // if its not a worker add it to the targets
                if (!enemyUnit.getType().isWorker())
                {
                    workersRemoved.push_back(enemyUnit);
                }
                // if it is a worker
                else
                {
                    for (const BaseLocation * enemyBaseLocation : m_bot.Bases().getOccupiedBaseLocations(Players::Enemy))
                    {
                        // only add it if it's in their region
                        if (enemyBaseLocation->containsPosition(enemyUnit.getPosition()))
                        {
                            workersRemoved.push_back(enemyUnit);
                        }
                    }
                }
            }

            // Allow micromanager to handle enemies
            executeMicro(workersRemoved);
        }
    }
}

const std::vector<Unit> & MicroManager::getUnits() const
{
    return m_units;
}

void MicroManager::regroup(const CCPosition & regroupPosition) const
{
    CCPosition ourBasePosition = m_bot.GetStartLocation();
    int regroupDistanceFromBase = m_bot.Map().getGroundDistance(regroupPosition, ourBasePosition);

    // for each of the units we have
    for (auto unit : m_units)
    {
        BOT_ASSERT(unit.isValid(), "null unit in MicroManager regroup");

        int unitDistanceFromBase = m_bot.Map().getGroundDistance(unit.getPosition(), ourBasePosition);

        // if the unit is outside the regroup area
        if (unitDistanceFromBase > regroupDistanceFromBase)
        {
            unit.move(ourBasePosition);
        }
        else if (Util::Dist(unit, regroupPosition) > 4)
        {
            // regroup it
            unit.move(regroupPosition);
        }
        else
        {
            unit.attackMove(unit.getPosition());
        }
    }
}

void MicroManager::trainSubUnits(const Unit & unit) const
{
    // TODO: something here
}