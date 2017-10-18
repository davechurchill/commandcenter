#include "FiniteStateMachine.h"

/*
    Duds so the compiler shuts up.
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

void FiniteStateMachine::update()
{
}
