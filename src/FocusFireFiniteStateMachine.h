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
    FocusFireFiniteStateMachine(const sc2::Unit *, const sc2::Unit * target, const std::vector<const sc2::Unit*> *, CCBot*);
    void update(const sc2::Unit * target, const std::vector<const sc2::Unit*> * targets, std::unordered_map<sc2::Tag, float> *unitHealth, CCBot* bot);
};