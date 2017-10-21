#include "Unit.h"
#include "CCBot.h"

Unit::Unit(CCUnit unit, CCBot & bot)
    : m_bot(bot)
    , m_unit(unit)
#ifdef SC2API
    , m_unitID(unit->tag)
#else
    , m_unitID(unit->getID())
#endif
{
    
}

CCUnit Unit::getUnitPtr() const
{
    return m_unit;
}

const CCRace & Unit::getRace() const
{
#ifdef SC2API
    return m_bot.Observation()->GetUnitTypeData()[getType()].race;
#else
    return getType().getRace();
#endif
}

const CCUnitType & Unit::getType() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->unit_type;
#else
    return m_unit->getType();
#endif
}

const CCPosition & Unit::getPosition() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->pos;
#else
    return m_unit->getPosition();
#endif
}

CCHealth Unit::getHitPoints() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->health;
#else
    return m_unit->currentHealth();
#endif
}

CCHealth Unit::getShields() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->shield;
#else
    return m_unit->getShields();
#endif
}

CCHealth Unit::getEnergy() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->energy;
#else
    return m_unit->getEnergy();
#endif
}

CCPlayer Unit::getPlayer() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    if (m_unit->alliance == sc2::Unit::Alliance::Self) { return 0; }
    else if (m_unit->alliance == sc2::Unit::Alliance::Enemy) { return 1; }
    else { return 2; }
#else
    if (m_unit->getPlayer() == BWAPI::Broodwar->self()) { return 0; }
    else if (m_unit->getPlayer() == BWAPI::Broodwar->enemy()) { return 1; }
    else { return 2; }
#endif
}

CCUnitID Unit::getID() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    CCUnitID id = m_unit->tag;
#else
    CCUnitID id = m_unit->getID();
#endif

    BOT_ASSERT(id == m_unitID, "Unit ID changed somehow");
    return id;
}

bool Unit::isCompleted() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->build_progress >= 1.0f;
#else
    return m_unit->isCompleted();
#endif
}

int Unit::getWeaponCooldown() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->weapon_cooldown;
#else
    return std::max(m_unit->getGroundWeaponCooldown(), m_unit->getAirWeaponCooldown());
#endif
}

bool Unit::isCloaked() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->cloak;
#else
    return m_unit->isCloaked();
#endif
}

bool Unit::isFlying() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->is_flying;
#else
    return m_unit->isFlying();
#endif
}

bool Unit::isAlive() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->is_alive;
#else
    return m_unit->getHitPoints() > 0;
#endif
}

bool Unit::isPowered() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->is_powered;
#else
    return m_unit->isPowered();
#endif
}

bool Unit::isIdle() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->orders.empty();
#else
    return m_unit->isIdle();
#endif
}

bool Unit::isBurrowed() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->is_burrowed;
#else
    return m_unit->isBurrowed();
#endif
}

bool Unit::isValid() const
{
    return m_unit && isAlive();
}

void Unit::stop()
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    m_bot.Actions()->UnitCommand(m_unit, sc2::ABILITY_ID::STOP);
#else
    m_unit->stop();
#endif
}

void Unit::attackUnit(const Unit & target)
{
    BOT_ASSERT(isValid(), "Unit is not valid");
    BOT_ASSERT(target.isValid(), "Target is not valid");
#ifdef SC2API
    m_bot.Actions()->UnitCommand(m_unit, sc2::ABILITY_ID::ATTACK_ATTACK, target.getUnitPtr());
#else
    m_unit->attackUnit(target.getUnitPtr());
#endif
}

void Unit::attackMove(const CCPosition & targetPosition)
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    m_bot.Actions()->UnitCommand(m_unit, sc2::ABILITY_ID::ATTACK_ATTACK, targetPosition);
#else
    m_unit->attack(targetPosition);
#endif
}

void Unit::move(const CCPosition & targetPosition)
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    m_bot.Actions()->UnitCommand(m_unit, sc2::ABILITY_ID::MOVE, targetPosition);
#else
    m_unit->move(targetPosition);
#endif
}

void Unit::move(const CCTilePosition & targetPosition)
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    m_bot.Actions()->UnitCommand(m_unit, sc2::ABILITY_ID::MOVE, CCPosition((float)targetPosition.x, (float)targetPosition.y));
#else
    m_unit->move(CCPosition(targetPosition));
#endif
}

void Unit::rightClick(const Unit & target)
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    m_bot.Actions()->UnitCommand(m_unit, sc2::ABILITY_ID::SMART, target.getUnitPtr());
#else
    m_unit->rightClick(target.getUnitPtr());
#endif
}

void Unit::repair(const Unit & target)
{
    rightClick(target);
}

void Unit::build(const CCUnitType & buildingType, CCTilePosition pos)
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    m_bot.Actions()->UnitCommand(m_unit, m_bot.Data(buildingType).buildAbility, Util::GetPosition(pos));
#else
    m_unit->build(buildingType, pos);
#endif
}

void Unit::buildTarget(const CCUnitType & buildingType, const Unit & target)
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    m_bot.Actions()->UnitCommand(m_unit, m_bot.Data(buildingType).buildAbility, target.getUnitPtr());
#else
    BOT_ASSERT(false, "buildTarget shouldn't be called for BWAPI bots");
#endif
}

void Unit::train(const CCUnitType & type)
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    m_bot.Actions()->UnitCommand(m_unit, m_bot.Data(type).buildAbility);
#else
    m_unit->train(type);
#endif
}
