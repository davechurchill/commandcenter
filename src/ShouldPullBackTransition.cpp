#include "ShouldPullBackTransition.h"
#include "Util.h"

ShouldPullBackTransition::ShouldPullBackTransition(const sc2::Unit * unit, const std::vector<const sc2::Unit*> * units, const sc2::Unit * target, CCFSMState* nextState)
{
    m_unit = unit;
    m_units = units;
    m_target = target;
    m_nextState = nextState;
}

bool ShouldPullBackTransition::isValid()
{
    float dist(Util::Dist(m_unit->pos, m_target->pos));
    float generalDist(Util::Dist(Util::CalcCenter(*m_units), m_target->pos));
    bool isNearer = dist < generalDist;
    bool isNearest = true;
    for (auto unit : *m_units)
    {
        float unitDist(Util::Dist(unit->pos, m_target->pos));
        if (unitDist < dist) isNearest = false;
    }

    return (m_unit->health / m_unit->health_max) < 0.5f && isNearer;
}
CCFSMState* ShouldPullBackTransition::getNextState()
{
    return m_nextState;
}

void ShouldPullBackTransition::onTransition() { }