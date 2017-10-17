#include "FocusFireFiniteStateMachine.h"
FocusFireFiniteStateMachine::FocusFireFiniteStateMachine() {};
FocusFireFiniteStateMachine::FocusFireFiniteStateMachine(const sc2::Unit * unit, const std::vector<const sc2::Unit*> * units, const sc2::Unit * target)
{
    CCFSMState* fireClosest = new FireClosestFSMState(unit, units, target);
    CCFSMState* pullBack = new PullBackFSMState(unit, units, target);
    initialState = fireClosest;
    activeState = initialState;
    activeState->onEnter();
}

void FocusFireFiniteStateMachine::update(const sc2::Unit * target, CCBot* bot)
{
    for (auto transition : this->activeState->getTransitions())
    {
        if (transition->isValid())
        {
            activeState->onExit();
            activeState = transition->getNextState();
            activeState->onEnter();
        }
    }
    activeState->onUpdate(target, bot);
}
