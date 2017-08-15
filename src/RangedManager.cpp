#include "RangedManager.h"
#include "Util.h"
#include "CCBot.h"

RangedManager::RangedManager(CCBot & bot)
    : MicroManager(bot)
{

}

void RangedManager::executeMicro(const std::vector<UnitTag> & targets)
{
    assignTargets(targets);
}

void RangedManager::assignTargets(const std::vector<UnitTag> & targets)
{
    const std::vector<UnitTag> & rangedUnits = getUnits();

    // figure out targets
    std::vector<UnitTag> rangedUnitTargets;
    for (auto & targetTag : targets)
    {
        auto target = m_bot.GetUnit(targetTag);

        if (!target) { continue; }
        if (target->unit_type == sc2::UNIT_TYPEID::ZERG_EGG) { continue; }
        if (target->unit_type == sc2::UNIT_TYPEID::ZERG_LARVA) { continue; }

        rangedUnitTargets.push_back(targetTag);
    }

    // for each meleeUnit
    for (auto & rangedUnitTag : rangedUnits)
    {
        auto meleeUnit = m_bot.GetUnit(rangedUnitTag);
        BOT_ASSERT(meleeUnit, "melee unit is null");

        // if the order is to attack or defend
        if (order.getType() == SquadOrderTypes::Attack || order.getType() == SquadOrderTypes::Defend)
        {
            if (!rangedUnitTargets.empty())
            {
                // find the best target for this meleeUnit
                UnitTag targetTag = getTarget(rangedUnitTag, rangedUnitTargets);

                // attack it
                if (m_bot.Config().KiteWithRangedUnits)
                {
                    Micro::SmartKiteTarget(rangedUnitTag, targetTag, m_bot);
                }
                else
                {
                    Micro::SmartAttackUnit(rangedUnitTag, targetTag, m_bot);
                }
            }
            // if there are no targets
            else
            {
                // if we're not near the order position
                if (Util::Dist(meleeUnit->pos, order.getPosition()) > 4)
                {
                    // move to it
                    Micro::SmartMove(rangedUnitTag, order.getPosition(), m_bot);
                }
            }
        }

        if (m_bot.Config().DrawUnitTargetInfo)
        {
            // TODO: draw the line to the unit's target
        }
    }
}

// get a target for the ranged unit to attack
// TODO: this is the melee targeting code, replace it with something better for ranged units
UnitTag RangedManager::getTarget(const UnitTag & meleeUnitTag, const std::vector<UnitTag> & targets)
{
    auto meleeUnit = m_bot.GetUnit(meleeUnitTag);
    BOT_ASSERT(meleeUnit, "null melee unit in getTarget");

    int highPriority = 0;
    double closestDist = std::numeric_limits<double>::max();
    UnitTag closestTarget = 0;

    // for each target possiblity
    for (auto & targetTag : targets)
    {
        auto targetUnit = m_bot.GetUnit(targetTag);
        BOT_ASSERT(targetUnit, "null target unit in getTarget");

        int priority = getAttackPriority(meleeUnitTag, targetTag);
        float distance = Util::Dist(meleeUnit->pos, targetUnit->pos);

        // if it's a higher priority, or it's closer, set it
        if (!closestTarget || (priority > highPriority) || (priority == highPriority && distance < closestDist))
        {
            closestDist = distance;
            highPriority = priority;
            closestTarget = targetTag;
        }
    }

    return closestTarget;
}

// get the attack priority of a type in relation to a zergling
int RangedManager::getAttackPriority(const UnitTag & attacker, const UnitTag & unitTag)
{
    auto unit = m_bot.GetUnit(unitTag);
    BOT_ASSERT(unit, "null unit in getAttackPriority");

    if (Util::IsCombatUnit(*unit, m_bot))
    {
        return 10;
    }

    if (Util::IsWorker(*unit))
    {
        return 9;
    }

    return 1;
}

