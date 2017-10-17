#include "FiniteStateMachine.h"

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
