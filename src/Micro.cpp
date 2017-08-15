#include "Micro.h"
#include "Util.h"
#include "CCBot.h"

const float dotRadius = 0.1f;

void Micro::SmartStop(const UnitTag & attacker, CCBot & bot)
{
    bot.Actions()->UnitCommand(attacker, sc2::ABILITY_ID::STOP);
}

void Micro::SmartAttackUnit(const UnitTag & attacker, const UnitTag & target, CCBot & bot)
{
    bot.Actions()->UnitCommand(attacker, sc2::ABILITY_ID::ATTACK_ATTACK, target);
}

void Micro::SmartAttackMove(const UnitTag & attacker, const sc2::Point2D & targetPosition, CCBot & bot)
{
    bot.Actions()->UnitCommand(attacker, sc2::ABILITY_ID::ATTACK_ATTACK, targetPosition);
}

void Micro::SmartMove(const UnitTag & attacker, const sc2::Point2D & targetPosition, CCBot & bot)
{
    bot.Actions()->UnitCommand(attacker, sc2::ABILITY_ID::MOVE, targetPosition);
}

void Micro::SmartRightClick(const UnitTag & unit, const UnitTag & target, CCBot & bot)
{
    bot.Actions()->UnitCommand(unit, sc2::ABILITY_ID::SMART, target);
}

void Micro::SmartRepair(const UnitTag & unit, const UnitTag & target, CCBot & bot)
{
    bot.Actions()->UnitCommand(unit, sc2::ABILITY_ID::SMART, target);
}

void Micro::SmartKiteTarget(const UnitTag & rangedUnit, const UnitTag & target, CCBot & bot)
{
    bot.Actions()->UnitCommand(rangedUnit, sc2::ABILITY_ID::ATTACK_ATTACK, target);
}

void Micro::SmartBuild(const UnitTag & builder, const sc2::UnitTypeID & buildingType, sc2::Point2D pos, CCBot & bot)
{
    bot.Actions()->UnitCommand(builder, bot.Data(buildingType).buildAbility, pos);
}

void Micro::SmartBuildTag(const UnitTag & builder, const sc2::UnitTypeID & buildingType, UnitTag targetTag, CCBot & bot)
{
    bot.Actions()->UnitCommand(builder, bot.Data(buildingType).buildAbility, targetTag);
}

void Micro::SmartTrain(const UnitTag & builder, const sc2::UnitTypeID & buildingType, CCBot & bot)
{
    bot.Actions()->UnitCommand(builder, bot.Data(buildingType).buildAbility);
}

void Micro::SmartAbility(const UnitTag & builder, const sc2::AbilityID & abilityID, CCBot & bot)
{
    bot.Actions()->UnitCommand(builder, abilityID);
}