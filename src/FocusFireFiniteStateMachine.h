#pragma once
#include "FocusFireFSM.h"

class CCBot;
class FocusFireFiniteStateMachine : FiniteStateMachine
{
private:
    FocusFireFSMState* initialState;
    FocusFireFSMState* activeState;
public:
    FocusFireFiniteStateMachine();
    FocusFireFiniteStateMachine(const sc2::Unit * unit, const std::vector<const sc2::Unit*> * units, const sc2::Unit * target);
    void update(const sc2::Unit * target, sc2::Point2D position, CCBot* bot);
};