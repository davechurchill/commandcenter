#include "Micro.h"
#include "Util.h"
#include "CCBot.h"

const float dotRadius = 0.1f;

void Micro::SmartStop(const sc2::Unit * attacker, CCBot & bot)
{
    BOT_ASSERT(attacker != nullptr, "Attacker is null");
    bot.Actions()->UnitCommand(attacker, sc2::ABILITY_ID::STOP);
}

void Micro::SmartAttackUnit(const sc2::Unit * attacker, const sc2::Unit * target, CCBot & bot)
{
    BOT_ASSERT(attacker != nullptr, "Attacker is null");
    BOT_ASSERT(target != nullptr, "Target is null");
    bot.Actions()->UnitCommand(attacker, sc2::ABILITY_ID::ATTACK_ATTACK, target);
}

void Micro::SmartAttackMove(const sc2::Unit * attacker, const sc2::Point2D & targetPosition, CCBot & bot)
{
    BOT_ASSERT(attacker != nullptr, "Attacker is null");
    bot.Actions()->UnitCommand(attacker, sc2::ABILITY_ID::ATTACK_ATTACK, targetPosition);
}

void Micro::SmartMove(const sc2::Unit * attacker, const sc2::Point2D & targetPosition, CCBot & bot)
{
    BOT_ASSERT(attacker != nullptr, "Attacker is null");
    bot.Actions()->UnitCommand(attacker, sc2::ABILITY_ID::MOVE, targetPosition);
}

void Micro::SmartRightClick(const sc2::Unit * unit, const sc2::Unit * target, CCBot & bot)
{
    BOT_ASSERT(unit != nullptr, "Unit is null");
    bot.Actions()->UnitCommand(unit, sc2::ABILITY_ID::SMART, target);
}

void Micro::SmartRepair(const sc2::Unit * unit, const sc2::Unit * target, CCBot & bot)
{
    BOT_ASSERT(unit != nullptr, "Unit is null");
    bot.Actions()->UnitCommand(unit, sc2::ABILITY_ID::SMART, target);
}

void Micro::SmartKiteTarget(const sc2::Unit * rangedUnit, const sc2::Unit * target, CCBot & bot)
{
    BOT_ASSERT(rangedUnit != nullptr, "RangedUnit is null");
    BOT_ASSERT(target != nullptr, "Target is null");
    sc2::UnitTypeData unitTypeData = bot.Observation()->GetUnitTypeData()[rangedUnit->unit_type];

    // use the correct weapon range regardless of target type
    float range(Util::GetAttackRangeForTarget(rangedUnit, target, bot));
    bool kite(true);
    float dist(Util::Dist(rangedUnit->pos, target->pos));
    float timeToEnter = std::max(0.f, (dist - range) / unitTypeData.movement_speed);

    kite = Util::IsCombatUnitType(target->unit_type, bot) && !(timeToEnter >= rangedUnit->weapon_cooldown);

    if (kite)
    {
        // if we can't shoot, run away
        sc2::Point2D fleePosition(rangedUnit->pos - target->pos + rangedUnit->pos);
        Micro::SmartMove(rangedUnit, fleePosition, bot);
    }
    else
    {
        // otherwise shoot
        Micro::SmartAttackUnit(rangedUnit, target, bot);
    }
}

void Micro::SmartFocusFire(const sc2::Unit * rangedUnit, const std::vector<const sc2::Unit *> rangedUnits, const sc2::Unit * target, CCBot & bot, std::map<sc2::Tag, FSMState*> &states)
{
    BOT_ASSERT(rangedUnit != nullptr, "RangedUnit is null");
    BOT_ASSERT(target != nullptr, "Target is null");

    // The Micro is the FSM
    /*
    FSMState* initialState = new FocusFireClosestFSMState(rangedUnit, target, &bot);
    FSMState* activeState;
    */
    // INITIALIZE STATES AND TRANSITIONS HERE
    // TODO: verifiy that state of unit is possible in this FSM. Otherwise unit changed BT leaf
    /*
    if (states.find(rangedUnit->tag) == states.end()) {
        activeState = initialState;
    }
    else activeState = states[rangedUnit->tag];

    bool isATransitionValid = false;
    for (auto transition : activeState->transitions)
    {
        if (transition->isValid())
        {
            activeState->onExit();
            activeState = transition->getNextState();
            activeState->onEnter();
            states.insert_or_assign(rangedUnit->tag, activeState);
        }
    }
    activeState->onUpdate();
    */

    // TODO: PUT THIS LOGIC IN STATES AND TRANSITIONS
    sc2::UnitTypeData unitTypeData = bot.Observation()->GetUnitTypeData()[rangedUnit->unit_type];

    // use the correct weapon range regardless of target type
    float range(Util::GetAttackRangeForTarget(rangedUnit, target, bot));
    bool kite(true);
    float dist(Util::Dist(rangedUnit->pos, target->pos));
    float timeToEnter = std::max(0.f, (dist - range) / unitTypeData.movement_speed);

    bool isNearest = true;

    for (auto unit : rangedUnits)
    {
        float unitDist(Util::Dist(unit->pos, target->pos));
        if (unitDist < dist) isNearest = false;
    }

    kite = !(timeToEnter >= rangedUnit->weapon_cooldown) && isNearest;

    if (kite)
    {
        sc2::Point2D fleePosition(rangedUnit->pos - target->pos + rangedUnit->pos);
        Micro::SmartMove(rangedUnit, fleePosition, bot);
    }
    else
    {
        // otherwise shoot
        Micro::SmartAttackUnit(rangedUnit, target, bot);
    }
}

void Micro::SmartBuild(const sc2::Unit * builder, const sc2::UnitTypeID & buildingType, sc2::Point2D pos, CCBot & bot)
{
    BOT_ASSERT(builder != nullptr, "Builder is null");
    bot.Actions()->UnitCommand(builder, bot.Data(buildingType).buildAbility, pos);
}

void Micro::SmartBuildTarget(const sc2::Unit * builder, const sc2::UnitTypeID & buildingType, const sc2::Unit * target, CCBot & bot)
{
    BOT_ASSERT(builder != nullptr, "Builder is null");
    BOT_ASSERT(target != nullptr, "Target is null");
    bot.Actions()->UnitCommand(builder, bot.Data(buildingType).buildAbility, target);
}

void Micro::SmartTrain(const sc2::Unit * builder, const sc2::UnitTypeID & buildingType, CCBot & bot)
{
    BOT_ASSERT(builder != nullptr, "Builder is null");
    bot.Actions()->UnitCommand(builder, bot.Data(buildingType).buildAbility);
}

void Micro::SmartAbility(const sc2::Unit * builder, const sc2::AbilityID & abilityID, CCBot & bot)
{
    BOT_ASSERT(builder != nullptr, "Builder is null");
    bot.Actions()->UnitCommand(builder, abilityID);
}