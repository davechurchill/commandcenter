#pragma once
#include "KitingFSM.h"

class CCBot;
class KitingFiniteStateMachine : public FiniteStateMachine
{
private:
    KitingFSMState* initialState;
    KitingFSMState* activeState;
public:
    KitingFiniteStateMachine();
    KitingFiniteStateMachine(const sc2::Unit * unit, const sc2::Unit * target);
    void update(const sc2::Unit * target, CCBot* bot);
};