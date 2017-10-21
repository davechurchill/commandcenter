#include "Micro.h"
#include "Util.h"
#include "CCBot.h"

const float dotRadius = 0.1f;

void Micro::SmartStop(CCUnit attacker, CCBot & bot)
{
    BOT_ASSERT(attacker != nullptr, "Attacker is null");

#ifdef SC2API
    bot.Actions()->UnitCommand(attacker, sc2::ABILITY_ID::STOP);
#else

#endif
}

void Micro::SmartAttackUnit(CCUnit attacker, CCUnit target, CCBot & bot)
{
    BOT_ASSERT(attacker != nullptr, "Attacker is null");
    BOT_ASSERT(target != nullptr, "Target is null");

#ifdef SC2API
    bot.Actions()->UnitCommand(attacker, sc2::ABILITY_ID::ATTACK_ATTACK, target);
#else

#endif
}

void Micro::SmartAttackMove(CCUnit attacker, const CCPosition & targetPosition, CCBot & bot)
{
    BOT_ASSERT(attacker != nullptr, "Attacker is null");

#ifdef SC2API
    bot.Actions()->UnitCommand(attacker, sc2::ABILITY_ID::ATTACK_ATTACK, targetPosition);
#else

#endif
}

void Micro::SmartMove(CCUnit attacker, const CCPosition & targetPosition, CCBot & bot)
{
    BOT_ASSERT(attacker != nullptr, "Attacker is null");

#ifdef SC2API
    bot.Actions()->UnitCommand(attacker, sc2::ABILITY_ID::MOVE, targetPosition);
#else

#endif
}

void Micro::SmartMove(CCUnit attacker, const CCTilePosition & targetTilePosition, CCBot & bot)
{
#ifdef SC2API
    SmartMove(attacker, CCPosition((float)targetTilePosition.x, (float)targetTilePosition.y), bot);
#else
    SmartMove(attacker, CCPosition(targetTilePosition), bot);
#endif
}

void Micro::SmartRightClick(const Unit & unit, CCUnit target, CCBot & bot)
{
    BOT_ASSERT(unit != nullptr, "Unit is null");

#ifdef SC2API
    bot.Actions()->UnitCommand(unit, sc2::ABILITY_ID::SMART, target);
#else

#endif
}

void Micro::SmartRepair(const Unit & unit, CCUnit target, CCBot & bot)
{
    BOT_ASSERT(unit != nullptr, "Unit is null");

#ifdef SC2API
    bot.Actions()->UnitCommand(unit, sc2::ABILITY_ID::SMART, target);
#else

#endif
}

void Micro::SmartKiteTarget(CCUnit rangedUnit, CCUnit target, CCBot & bot)
{
    BOT_ASSERT(rangedUnit != nullptr, "RangedUnit is null");
    BOT_ASSERT(target != nullptr, "Target is null");

#ifdef SC2API
    bot.Actions()->UnitCommand(rangedUnit, sc2::ABILITY_ID::ATTACK_ATTACK, target);
#else

#endif
}

void Micro::SmartBuild(CCUnit builder, const CCUnitType & buildingType, CCTilePosition pos, CCBot & bot)
{
    BOT_ASSERT(builder != nullptr, "Builder is null");

#ifdef SC2API
    bot.Actions()->UnitCommand(builder, bot.Data(buildingType).buildAbility, Util::GetPosition(pos));
#else

#endif
}

void Micro::SmartBuildTarget(CCUnit builder, const CCUnitType & buildingType, CCUnit target, CCBot & bot)
{
    BOT_ASSERT(builder != nullptr, "Builder is null");
    BOT_ASSERT(target != nullptr, "Target is null");

#ifdef SC2API
    bot.Actions()->UnitCommand(builder, bot.Data(buildingType).buildAbility, target);
#else

#endif
}

void Micro::SmartTrain(CCUnit builder, const CCUnitType & buildingType, CCBot & bot)
{
    BOT_ASSERT(builder != nullptr, "Builder is null");

#ifdef SC2API
    bot.Actions()->UnitCommand(builder, bot.Data(buildingType).buildAbility);
#else

#endif
}

void Micro::SmartAbility(CCUnit builder, const sc2::AbilityID & abilityID, CCBot & bot)
{
    BOT_ASSERT(builder != nullptr, "Builder is null");

#ifdef SC2API
    bot.Actions()->UnitCommand(builder, abilityID);
#else

#endif
}