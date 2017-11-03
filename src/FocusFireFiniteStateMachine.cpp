#include "FocusFireFiniteStateMachine.h"
#include "FireClosestFSMState.h"
#include "PullBackFSMState.h"

FocusFireFiniteStateMachine::FocusFireFiniteStateMachine() {};
FocusFireFiniteStateMachine::FocusFireFiniteStateMachine(const sc2::Unit * unit, const sc2::Unit * target, const std::vector<const sc2::Unit*> * targets, CCBot* bot)
{
    FocusFireFSMState* fireClosest = new FireClosestFSMState(unit, target);
    FocusFireFSMState* pullBack = new PullBackFSMState(unit, target);
    initialState = fireClosest;
    activeState = initialState;
    activeState->onEnter(targets, bot);
}

void FocusFireFiniteStateMachine::update(const sc2::Unit * target, const std::vector<const sc2::Unit*> * targets, const std::vector<const sc2::Unit*> * units, std::unordered_map<sc2::Tag, float> * unitHealth, CCBot* bot)
{
    for (auto transition : activeState->getTransitions())
    {
        if (transition->isValid(units, unitHealth, bot))
        {
            activeState->onExit();
            activeState = transition->getNextState();
            activeState->onEnter(targets, bot);
        }
    }
    activeState->onUpdate(target, bot);
}
