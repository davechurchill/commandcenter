#pragma once
#include "DonePullBackTransition.h"
#include "Util.h"

DonePullBackTransition::DonePullBackTransition(const sc2::Unit * unit, sc2::Point2D position, FocusFireFSMState* nextState)
{
    m_unit = unit;
    m_nextState = nextState;
    m_position = position;
}

bool DonePullBackTransition::isValid(const sc2::Unit * target, const std::vector<const sc2::Unit*> * units, std::unordered_map<sc2::Tag, float> *, CCBot*)
{
    bool done(false);
    done = m_position == m_unit->pos;
    if (Util::Dist(m_position, m_unit->pos) < 1.5f)
        return true;
    else
        return false;
}

FocusFireFSMState* DonePullBackTransition::getNextState()
{
    return m_nextState;
}

void DonePullBackTransition::onTransition() 
{ 

}
