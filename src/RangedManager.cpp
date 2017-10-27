#include "RangedManager.h"
#include "Util.h"
#include "CCBot.h"
#include "Behavior.h"
#include <algorithm>

RangedManager::RangedManager(CCBot & bot)
    : MicroManager(bot)
{
    m_rallied = false;
}

void RangedManager::executeMicro(const std::vector<const sc2::Unit *> & targets)
{
    // build bt tree here
    assignTargets(targets);
}

void RangedManager::assignTargets(const std::vector<const sc2::Unit *> & targets)
{
    const std::vector<const sc2::Unit *> & rangedUnits = getUnits();

    // figure out targets
    std::vector<const sc2::Unit *> rangedUnitTargets;
    for (auto target : targets)
    {
        if (!target) { continue; }
        if (target->unit_type == sc2::UNIT_TYPEID::ZERG_EGG) { continue; }
        if (target->unit_type == sc2::UNIT_TYPEID::ZERG_LARVA) { continue; }

        rangedUnitTargets.push_back(target);
    }
    // if the order is to attack or defend
    if (order.getType() == SquadOrderTypes::Attack || order.getType() == SquadOrderTypes::Defend)
    {
        if (!rangedUnitTargets.empty())
        {
            sc2::Point2D targetCenterPoint = Util::CalcCenter(rangedUnitTargets);
            sc2::Point2D unitCenterPoint = Util::CalcCenter(rangedUnits);
            //reset the rallied state if units are too far from enemy units
            if (m_rallied)
                m_rallied = Util::Dist(unitCenterPoint, targetCenterPoint) < 10;
            if (!m_rallied)
            {
                //calculate a line that define the shape of the enemy group
                sc2::Point2D targetsShape = Util::CalcLinearRegression(rangedUnitTargets);
                //calculate the perpendicular vectors to find the front of the enemy group
                sc2::Point2D direction = Util::CalcPerpendicularVector(targetsShape);
                sc2::Point2D oppositeDirection(-direction.x, -direction.y);
                //make sure the perpendicular vector is in the right direction
                if (Util::Dist(targetCenterPoint + direction, unitCenterPoint) > Util::Dist(targetCenterPoint + oppositeDirection, unitCenterPoint))
                    direction = oppositeDirection;
                //the rally point is set 8 meters in front of the enemy units
                sc2::Point2D rallyPoint = targetCenterPoint + direction * 8;
                bool allUnitsPlaced(true);
                float hardcodedSpaceBetweenUnits = 2.5f;
                for (int i = 0; i < rangedUnits.size(); i++)
                {
                    auto unit = rangedUnits.at(i);
                    if (Util::Dist(unit->pos, targetCenterPoint) < 7)
                    {
                        allUnitsPlaced = true;
                        break;
                    }
                    float radius = unit->radius;
                    sc2::Point2D unitRallyPoint;
                    if (i % 2 == 0)
                    {
                        unitRallyPoint = rallyPoint + targetsShape * (i / 2) * radius * hardcodedSpaceBetweenUnits;
                    }
                    else
                    {
                        unitRallyPoint = rallyPoint - targetsShape * ((i + 1) / 2) * radius * hardcodedSpaceBetweenUnits;
                    }
                    m_bot.Actions()->UnitCommand(unit, sc2::ABILITY_ID::MOVE, unitRallyPoint);
                    if (Util::Dist(unit->pos, unitRallyPoint) > 0.5f)
                    {
                        //flag as not placed only if position is within map bounds
                        //if(unitRallyPoint.x > 0 && unitRallyPoint.x < m_bot.Map().width() && unitRallyPoint.y > 0 && unitRallyPoint.y < m_bot.Map().height())
                        //hardcoded for minigame maps because the Map infos are incoherent with the positions of the units
                        if(unitRallyPoint.x > 20 && unitRallyPoint.x < 35 && unitRallyPoint.y > 20 && unitRallyPoint.y < 35)
                            allUnitsPlaced = false;
                    }
                }
                if (!allUnitsPlaced)
                    return;
                m_rallied = true;
            }

            // for each rangedUnit
            for (auto rangedUnit : rangedUnits)
            {
                BOT_ASSERT(rangedUnit, "ranged unit is null");

                // find the best target for this rangedUnit
                const sc2::Unit * target = getTarget(rangedUnit, rangedUnitTargets);

                if (isTargetRanged(target))
                {
                    Micro::SmartFocusFire(rangedUnit, target, &rangedUnitTargets, m_bot, m_focusFireStates, m_unitHealth);
                }
                // attack it
                else if (m_bot.Config().KiteWithRangedUnits)
                {
                    Micro::SmartKiteTarget(rangedUnit, target, m_bot, m_kittingStates);
                }
                else
                {
                    Micro::SmartAttackUnit(rangedUnit, target, m_bot);
                }
            }
        }
        // if there are no targets
        else
        {
            // for each rangedUnit
            for (auto rangedUnit : rangedUnits)
            {
                BOT_ASSERT(rangedUnit, "ranged unit is null");

                // if we're not near the order position
                if (Util::Dist(rangedUnit->pos, order.getPosition()) > 4)
                {
                    // move to it
                    Micro::SmartMove(rangedUnit, order.getPosition(), m_bot);
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
const sc2::Unit * RangedManager::getTarget(const sc2::Unit * rangedUnit, const std::vector<const sc2::Unit *> & targets)
{
    BOT_ASSERT(rangedUnit, "null ranged unit in getTarget");

    int highPriority = 0;
    double closestDist = std::numeric_limits<double>::max();
    const sc2::Unit * closestTarget = nullptr;

    // for each target possiblity
    for (auto targetUnit : targets)
    {
        BOT_ASSERT(targetUnit, "null target unit in getTarget");

        int priority = getAttackPriority(rangedUnit, targetUnit);
        float distance = 0;
        if (isTargetRanged(targetUnit))
            distance = Util::Dist(Util::CalcCenter(getUnits()), targetUnit->pos);
        else
            distance = Util::Dist(rangedUnit->pos, targetUnit->pos);

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

// TODO: instead of returning an hardcoded int, calculate a threat score based on dps, distance and other factors
float RangedManager::getAttackPriority(const sc2::Unit * attacker, const sc2::Unit * target)
{
    BOT_ASSERT(target, "null unit in getAttackPriority");

    if (Util::IsCombatUnit(target, m_bot))
    {
        float remainingHealth = 1 - (target->health / target->health_max);
        sc2::UnitTypeData unitTypeData = Util::GetUnitTypeDataFromUnitTypeId(target->unit_type, m_bot);
        float dps = 0.f;
        for (sc2::Weapon & weapon : unitTypeData.weapons)
        {
            float weaponDps = weapon.attacks * weapon.damage_ * (1 / weapon.speed);
            dps = std::max(weaponDps, dps);
        }
        return 5 + (dps * remainingHealth);
    }

    if (Util::IsWorker(target))
    {
        return 2;
    }

    return 1;
}

// according to http://wiki.teamliquid.net/starcraft2/Range
// the maximum range of a melee unit is 1 (ultralisk)
bool RangedManager::isTargetRanged(const sc2::Unit * target)
{
    BOT_ASSERT(target, "target is null");
    sc2::UnitTypeData unitTypeData = Util::GetUnitTypeDataFromUnitTypeId(target->unit_type, m_bot);
    float maxRange = 0.f;

    for (sc2::Weapon & weapon : unitTypeData.weapons)
        maxRange = std::max(maxRange, weapon.range);
    return maxRange > 1.f;
}

