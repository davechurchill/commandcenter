#include "Unit.h"

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

CCUnit Unit::getRawUnit() const
{
    return m_unit;
    m_unit->
}

const CCPosition & Unit::pos() const
{
#ifdef SC2API
    return m_unit->pos;
#else
    return m_unit->getPosition();
#endif
}

const CCHealth & Unit::health() const
{
#ifdef SC2API
    return m_unit->health;
#else
    return m_unit->currentHealth();
#endif
}