#include "ShouldPullBackTransition.h"
#include "Util.h"
#include "CCBot.h"

ShouldPullBackTransition::ShouldPullBackTransition(const sc2::Unit * unit, const sc2::Unit * target, FocusFireFSMState* nextState)
{
    m_unit = unit;
    m_target = target;
    m_nextState = nextState;
}

bool ShouldPullBackTransition::isValid(std::map<sc2::Tag, float> * unitHealth, CCBot* bot)
{
    auto targetWeapons = bot->Observation()->GetUnitTypeData()[m_target->unit_type].weapons;
    float damage = 0.f;
    for (auto weapon : targetWeapons)
        if (weapon.damage_ > damage) damage = weapon.damage_;

    if (unitHealth->find(m_unit->tag) == unitHealth->end())
        unitHealth->insert_or_assign(m_unit->tag, m_unit->health);
    float previousHealth = unitHealth->at(m_unit->tag);

    bool shouldBack = previousHealth > m_unit->health && m_unit->health <= (damage * 2);
    unitHealth->insert_or_assign(m_unit->tag, m_unit->health);
    return shouldBack;
}
FocusFireFSMState* ShouldPullBackTransition::getNextState()
{
    return m_nextState;
}

void ShouldPullBackTransition::onTransition() { }