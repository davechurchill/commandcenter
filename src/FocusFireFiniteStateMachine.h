#pragma once
#include "FiniteStateMachine.h"
#include "DonePullBackTransition.h"
#include "FireClosestFSMState.h"
#include "PullBackFSMState.h"
#include "ShouldPullBackTransition.h"

class CCBot;
class FocusFireFiniteStateMachine  : public CCFiniteStateMachine
{
private:
    CCFSMState* initialState;
    CCFSMState* activeState;
public:
    FocusFireFiniteStateMachine();
    FocusFireFiniteStateMachine(const sc2::Unit * unit, const std::vector<const sc2::Unit*> * units, const sc2::Unit * target);
    void update(const sc2::Unit * target, CCBot* bot);
};