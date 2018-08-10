#include "StalkerManager.h"
#include "Util.h"
#include "CCBot.h"

const double pi = 3.14159265358979323846;

StalkerManager::StalkerManager(CCBot & bot)
    : MicroManager(bot)
{

}

void StalkerManager::executeMicro(const std::vector<Unit> & targets)
{
    assignTargets(targets);
}

#ifdef SC2API
void StalkerManager::assignTargets(const std::vector<Unit> & targets)
{
    const std::vector<Unit> & stalkerUnits = getUnits();

    // figure out targets
    std::vector<Unit> stalkerUnitTargets;
    for (auto target : targets)
    {
        if (!target.isValid()) { continue; }
        if (target.getType().isEgg()) { continue; }
        if (target.getType().isLarva()) { continue; }

        stalkerUnitTargets.push_back(target);
    }

    // for each stalkerUnit
    for (auto stalkerUnit : stalkerUnits)
    {
        BOT_ASSERT(stalkerUnit.isValid(), "stalker unit is null");

        // if the order is to attack or defend
        if (order.getType() == SquadOrderTypes::Attack || order.getType() == SquadOrderTypes::Defend)
        {
            if (!stalkerUnitTargets.empty())
            {
                // find the best target for this Unit
                Unit target = getTarget(stalkerUnit, stalkerUnitTargets);
				
				if (stalkerUnit.getShields() < 80)
				{
					// 8 is max range of bilnk
					float blinkRange = 8.0;
					float newX = blinkRange * cos(stalkerUnit.getUnitPtr()->facing + pi);
					float newY = blinkRange * sin(stalkerUnit.getUnitPtr()->facing + pi);
					
					sc2::Point2D newPos = sc2::Point2D(stalkerUnit.getPosition().x + newX, stalkerUnit.getPosition().y + newY);
					
					int counter = blinkRange * 2;

					// attempted checking for invalid blink positioning and fix?
					while (!m_bot.Map().isValidTile(newPos.x, newPos.y) || counter > 0)
					{
						if (counter % 2 == 0)
						{
							newPos.x--;
						}
						else 
						{
							newPos.y--;
						}
						counter--;
					}

					// should be fine using sc2 api stuff here since stalkers are not in sc1
					stalkerUnit.useAbility(sc2::ABILITY_ID::EFFECT_BLINK_STALKER, newPos);
				}

                // attack it
                if (m_bot.Config().KiteWithRangedUnits)
                {	
                    // TODO: implement kiting
					if (stalkerUnit.getType().getAttackRange() > target.getType().getAttackRange()) 
					{
					
					}
					
					stalkerUnit.attackUnit(target);
                }
                else
                {
                    stalkerUnit.attackUnit(target);
                }
				if (m_bot.Config().DrawUnitTargetInfo)
				{
					// TODO: fix lines on death
					// does not delete lines on death
					m_bot.Map().drawLine(stalkerUnit.getPosition().x, stalkerUnit.getPosition().y, target.getPosition().x, target.getPosition().y, CCColor(255, 0, 255));
					
				}
            }
            // if there are no targets
            else
            {
                // if we're not near the order position
                if (Util::Dist(stalkerUnit, order.getPosition()) > 4)
                {
                    // move to it
                    stalkerUnit.move(order.getPosition());
                }
            }
        }
    }
}

#endif

// get a target for the stalker unit to attack
// TODO: this is the melee targeting code, replace it with something better for stalker units
Unit StalkerManager::getTarget(const Unit & stalkerUnit, const std::vector<Unit> & targets)
{
    BOT_ASSERT(stalkerUnit.isValid(), "null melee unit in getTarget");

    int highPriority = 0;
    double closestDist = std::numeric_limits<double>::max();
    Unit closestTarget;

    // for each target possiblity
    for (auto & targetUnit : targets)
    {
        BOT_ASSERT(targetUnit.isValid(), "null target unit in getTarget");

        int priority = getAttackPriority(stalkerUnit, targetUnit);
        float distance = Util::Dist(stalkerUnit, targetUnit);

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
int StalkerManager::getAttackPriority(const Unit & attacker, const Unit & target)
{
    BOT_ASSERT(target.isValid(), "null unit in getAttackPriority");

    if (target.getType().isCombatUnit())
    {
        return 10;
    }

    if (target.getType().isWorker())
    {
        return 9;
    }

    return 1;
}

