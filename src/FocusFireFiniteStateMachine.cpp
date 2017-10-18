#include "FocusFireFiniteStateMachine.h"
FocusFireFiniteStateMachine::FocusFireFiniteStateMachine() {};
FocusFireFiniteStateMachine::FocusFireFiniteStateMachine(const sc2::Unit * unit, const std::vector<const sc2::Unit*> * units, const sc2::Unit * target)
{
    FocusFireFSMState* fireClosest = new FireClosestFSMState(unit, units, target);
    FocusFireFSMState* pullBack = new PullBackFSMState(unit, units, target);
    initialState = fireClosest;
    activeState = initialState;
    activeState->onEnter();
}

void FocusFireFiniteStateMachine::update(const sc2::Unit * target, sc2::Point2D position, CCBot* bot)
{
    for (auto transition : this->activeState->getTransitions())
    {
        if (transition->isValid(position))
        {
            activeState->onExit();
            activeState = transition->getNextState();
            activeState->onEnter();
        }
    }
    activeState->onUpdate(target, bot);
}
