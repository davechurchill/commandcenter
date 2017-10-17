#pragma once
#include "FocusFireFiniteStateMachine.h"
#include "Util.h"

DonePullBackTransition::DonePullBackTransition(const sc2::Unit * unit, sc2::Point2D position, CCFSMState* nextState)
{
    m_unit = unit;
    m_nextState = nextState;
    m_position = position;
}

bool DonePullBackTransition::isValid()
{
    bool done(false);
    done = m_position == m_unit->pos;
    if (Util::Dist(m_position, m_unit->pos) < 1.f)
        return true;
    else
        return false;
}
CCFSMState* DonePullBackTransition::getNextState()
{
    return m_nextState;
}

void DonePullBackTransition::onTransition() 
{ 

}
