#include "FiniteStateMachine.h"

/*
    Duds to the compiler shuts up.
*/

bool FSMTransition::isValid()
{
    return false;
}

FSMState * FSMTransition::getNextState()
{
    return nullptr;
}

void FSMTransition::onTransition()
{
}

void FSMState::onEnter()
{
}

void FSMState::onUpdate()
{
}

void FSMState::onExit()
{
}

void CCFSMState::onUpdate(const sc2::Unit * m_target, CCBot* bot)
{
}

std::vector<CCFSMTransition*> CCFSMState::getTransitions()
{
    return std::vector<CCFSMTransition*>();
}

CCFSMState * CCFSMTransition::getNextState()
{
    return nullptr;
}

void CCFiniteStateMachine::update(const sc2::Unit * target, CCBot * bot)
{
}
