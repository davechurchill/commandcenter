#include "ShouldPullBackTransition.h"
#include "Util.h"

ShouldPullBackTransition::ShouldPullBackTransition(const sc2::Unit * unit, const std::vector<const sc2::Unit*> * units, const sc2::Unit * target, FocusFireFSMState* nextState)
{
    m_unit = unit;
    m_units = units;
    m_target = target;
    m_nextState = nextState;
}

bool ShouldPullBackTransition::isValid(sc2::Point2D position)
{
    float dist(Util::Dist(m_unit->pos, position));
    float health = m_unit->health / m_unit->health_max;
    float meanHealth = 0.f;
    float meanDist = 0.f;
    for (auto unit : *m_units)
    {
        meanHealth += (unit->health / unit->health_max);
        meanDist += Util::Dist(unit->pos, position);
    }
    meanHealth /= m_units->size();
    meanDist /= m_units->size();
    if (dist < meanDist && health < meanHealth / 2.3f)
        return true;
    else
        return false;
}
FocusFireFSMState* ShouldPullBackTransition::getNextState()
{
    return m_nextState;
}

void ShouldPullBackTransition::onTransition() { }