#include "KitingFiniteStateMachine.h"
#include "AttackFSMState.h"
#include "FleeFSMState.h"

KitingFiniteStateMachine::KitingFiniteStateMachine() {}
KitingFiniteStateMachine::KitingFiniteStateMachine(const sc2::Unit * unit, const sc2::Unit * target)
{
    KitingFSMState* attack = new AttackFSMState(unit,target);
    KitingFSMState* flee = new FleeFSMState(unit, target);
    initialState = attack;
    activeState = initialState;
    activeState->onEnter();

}
void KitingFiniteStateMachine::update(const sc2::Unit * target, CCBot* bot)
{
    for (auto transition : activeState->getTransitions())
    {
        if (transition->isValid(target, bot))
        {
            activeState->onExit();
            activeState = transition->getNextState();
            activeState->onEnter();
        }
    }
    activeState->onUpdate(target, bot);
}