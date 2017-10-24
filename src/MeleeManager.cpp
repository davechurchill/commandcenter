#include "MeleeManager.h"
#include "Util.h"
#include "CCBot.h"

MeleeManager::MeleeManager(CCBot & bot)
    : MicroManager(bot)
{

}

void MeleeManager::executeMicro(const std::vector<Unit> & targets)
{
    assignTargets(targets);
}

void MeleeManager::assignTargets(const std::vector<Unit> & targets)
{
    const std::vector<Unit> & meleeUnits = getUnits();

    // figure out targets
    std::vector<Unit> meleeUnitTargets;
    for (auto target : targets)
    {
        if (!target.isValid()) { continue; }
        if (target.isFlying()) { continue; }
        if (target.getType().isEgg()) { continue; }
        if (target.getType().isLarva()) { continue; }

        meleeUnitTargets.push_back(target);
    }

    // for each meleeUnit
    for (auto & meleeUnit : meleeUnits)
    {
        BOT_ASSERT(meleeUnit.isValid(), "melee unit is null");

        // if the order is to attack or defend
        if (order.getType() == SquadOrderTypes::Attack || order.getType() == SquadOrderTypes::Defend)
        {
            // run away if we meet the retreat critereon
            if (meleeUnitShouldRetreat(meleeUnit, targets))
            {
                CCPosition fleeTo(m_bot.GetStartLocation());

                meleeUnit.move(fleeTo);
            }
            // if there are targets
            else if (!meleeUnitTargets.empty())
            {
                // find the best target for this meleeUnit
                Unit target = getTarget(meleeUnit, meleeUnitTargets);

                // attack it
                meleeUnit.attackUnit(target);
            }
            // if there are no targets
            else
            {
                // if we're not near the order position
                if (Util::Dist(meleeUnit, order.getPosition()) > 4)
                {
                    // move to it
                    meleeUnit.move(order.getPosition());
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
Unit MeleeManager::getTarget(Unit meleeUnit, const std::vector<Unit> & targets)
{
    BOT_ASSERT(meleeUnit.isValid(), "null melee unit in getTarget");

    int highPriority = 0;
    double closestDist = std::numeric_limits<double>::max();
    Unit closestTarget;

    // for each target possiblity
    for (auto & targetUnit : targets)
    {
        BOT_ASSERT(targetUnit.isValid(), "null target unit in getTarget");

        int priority = getAttackPriority(meleeUnit, targetUnit);
        float distance = Util::Dist(meleeUnit, targetUnit);

        // if it's a higher priority, or it's closer, set it
        if (!closestTarget.isValid() || (priority > highPriority) || (priority == highPriority && distance < closestDist))
        {
            closestDist = distance;
            highPriority = priority;
            closestTarget = targetUnit;
        }
    }

    return closestTarget;
}

// get the attack priority of a type in relation to a zergling
int MeleeManager::getAttackPriority(Unit attacker, const Unit & unit)
{
    BOT_ASSERT(unit.isValid(), "null unit in getAttackPriority");

    if (unit.getType().isCombatUnit())
    {
        return 10;
    }

    if (unit.getType().isWorker())
    {
        return 9;
    }

    return 1;
}

bool MeleeManager::meleeUnitShouldRetreat(Unit meleeUnit, const std::vector<Unit> & targets)
{
    // TODO: should melee units ever retreat?
    return false;
}
