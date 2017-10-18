#include "FocusFireFSM.h"
/*
Duds so the compiler shuts up.
*/

void FocusFireFSMState::onUpdate(const sc2::Unit * m_target, CCBot* bot)
{
}

std::vector<FocusFireFSMTransition*> FocusFireFSMState::getTransitions()
{
    return std::vector<FocusFireFSMTransition*>();
}

FocusFireFSMState * FocusFireFSMTransition::getNextState()
{
    return nullptr;
}

bool FocusFireFSMTransition::isValid(sc2::Point2D)
{
    return false;
}

void FocusFireFiniteStateMachine::update(const sc2::Unit * target, sc2::Point2D position, CCBot * bot)
{
}
