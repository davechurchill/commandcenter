#include "RangedManager.h"
#include "Util.h"
#include "CCBot.h"
#include "BehaviorTreeBuilder.h"
#include "RangedActions.h"
#include <algorithm>


RangedManager::RangedManager(CCBot & bot)
    : MicroManager(bot)
{ }

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
    // for each rangedUnit
    for (auto rangedUnit : rangedUnits)
    {
        BOT_ASSERT(rangedUnit, "ranged unit is null");

        const sc2::Unit * target = nullptr;
        const sc2::Unit * mineral = nullptr;
        sc2::Point2D mineralPos;

        ConditionAction isEnemyInSight(rangedUnitTargets.size() > 0 && (target = getTarget(rangedUnit, rangedUnitTargets)) != nullptr),
            isMineralInSight((mineral = getClosestMineral(rangedUnit)) != nullptr),
            isEnemyRanged(target != nullptr && isTargetRanged(target));

        if (mineral == nullptr) mineralPos = sc2::Point2D(0, 0);
        else mineralPos = mineral->pos;

        FocusFireAction focusFireAction(rangedUnit, target, &rangedUnitTargets, m_bot, m_focusFireStates, m_unitHealth);
        KiteAction kiteAction(rangedUnit, target, m_bot, m_kittingStates);
        GoToMineralShardAction goToMineralShardAction(rangedUnit, mineralPos, m_bot);
        GoToObjectiveAction goToObjectiveAction(rangedUnit, order.getPosition(), m_bot);

        BehaviorTree* bt = BehaviorTreeBuilder()
            .selector()
            .sequence()
            .condition(&isEnemyInSight).end()
            .selector()
            .sequence()
            .condition(&isEnemyRanged).end()
            .action(&focusFireAction).end()
            .end()
            .action(&kiteAction).end()
            .end()
            .end()
            .sequence()
            .condition(&isMineralInSight).end()
            .action(&goToMineralShardAction).end()
            .end()
            .action(&goToObjectiveAction).end()
            .end()
            .end();

        bt->tick();
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

        float priority = getAttackPriority(rangedUnit, targetUnit);
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

const sc2::Unit * RangedManager::getClosestMineral(const sc2::Unit * unit) {
    const sc2::Unit * closestShard = nullptr;
    auto potentialMinerals = m_bot.Observation()->GetUnits(sc2::Unit::Alliance::Neutral);
    for (auto mineral : potentialMinerals)
    {
        if (closestShard == nullptr && mineral->is_on_screen) {
            closestShard = mineral;
        }
        else if (mineral->unit_type == 1680 && Util::Dist(mineral->pos, unit->pos) < Util::Dist(closestShard->pos, unit->pos) && mineral->is_on_screen) {
            closestShard = mineral;
        }
    }
    return closestShard;
}

