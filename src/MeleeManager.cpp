#include "MeleeManager.h"
#include "Util.h"
#include "CCBot.h"

MeleeManager::MeleeManager(CCBot & bot)
    : MicroManager(bot)
{

}

void MeleeManager::executeMicro(const std::vector<const sc2::Unit *> & targets)
{
    assignTargets(targets);
}

void MeleeManager::assignTargets(const std::vector<const sc2::Unit *> & targets)
{
    const std::vector<const sc2::Unit *> & meleeUnits = getUnits();

    // figure out targets
    std::vector<const sc2::Unit *> meleeUnitTargets;
    for (auto target : targets)
    {
        if (!target) { continue; }
        if (target->is_flying) { continue; }
        if (target->unit_type == sc2::UNIT_TYPEID::ZERG_EGG) { continue; }
        if (target->unit_type == sc2::UNIT_TYPEID::ZERG_LARVA) { continue; }

        meleeUnitTargets.push_back(target);
    }

    // for each meleeUnit
    for (auto & meleeUnit : meleeUnits)
    {
        BOT_ASSERT(meleeUnit, "melee unit is null");

        // if the order is to attack or defend
        if (order.getType() == SquadOrderTypes::Attack || order.getType() == SquadOrderTypes::Defend)
        {
            // run away if we meet the retreat critereon
            if (meleeUnitShouldRetreat(meleeUnit, targets))
            {
                sc2::Point2D fleeTo(m_bot.GetStartLocation());

                Micro::SmartMove(meleeUnit, fleeTo, m_bot);
            }
            // if there are targets
            else if (!meleeUnitTargets.empty())
            {
                // find the best target for this meleeUnit
                const sc2::Unit * target = getTarget(meleeUnit, meleeUnitTargets);

                // attack it
                Micro::SmartAttackUnit(meleeUnit, target, m_bot);
            }
            // if there are no targets
            else
            {
                // if we're not near the order position
                if (Util::Dist(meleeUnit->pos, order.getPosition()) > 4)
                {
                    // move to it
                    Micro::SmartMove(meleeUnit, order.getPosition(), m_bot);
                }
            }
        }

        if (m_bot.Config().DrawUnitTargetInfo)
        {
            // TODO: draw the line to the unit's target
        }
    }
}

// get a target for the meleeUnit to attack
const sc2::Unit * MeleeManager::getTarget(const sc2::Unit * meleeUnit, const std::vector<const sc2::Unit *> & targets)
{
    BOT_ASSERT(meleeUnit, "null melee unit in getTarget");

    int highPriority = 0;
    double closestDist = std::numeric_limits<double>::max();
    const sc2::Unit * closestTarget = nullptr;

    // for each target possiblity
    for (auto & targetUnit : targets)
    {
        BOT_ASSERT(targetUnit, "null target unit in getTarget");

        int priority = getAttackPriority(meleeUnit, targetUnit);
        float distance = Util::Dist(meleeUnit->pos, targetUnit->pos);

        // if it's a higher priority, or it's closer, set it
        if (!closestTarget || (priority > highPriority) || (priority == highPriority && distance < closestDist))
        {
            closestDist = distance;
            highPriority = priority;
            closestTarget = targetUnit;
        }
    }

    return closestTarget;
}

// get the attack priority of a type in relation to a zergling
int MeleeManager::getAttackPriority(const sc2::Unit * attacker, const sc2::Unit * unit)
{
    BOT_ASSERT(unit, "null unit in getAttackPriority");

    if (Util::IsCombatUnit(unit, m_bot))
    {
        return 10;
    }

    if (Util::IsWorker(unit))
    {
        return 9;
    }

    return 1;
}

bool MeleeManager::meleeUnitShouldRetreat(const sc2::Unit * meleeUnit, const std::vector<const sc2::Unit *> & targets)
{
    // TODO: should melee units ever retreat?
    return false;
}
