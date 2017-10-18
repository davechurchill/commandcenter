#pragma once
#include "FiniteStateMachine.h"

class FocusFireFSMTransition;
class FocusFireFSMState : public FSMState
{
public:
    virtual void onUpdate(const sc2::Unit * m_target, CCBot*);
    virtual void onEnter(const std::vector<const sc2::Unit*> *, CCBot*);
    virtual std::vector<FocusFireFSMTransition*> getTransitions();
};

class FocusFireFSMTransition : public FSMTransition
{
public:
    virtual FocusFireFSMState* getNextState();
    virtual bool isValid(std::map<sc2::Tag, float> *, CCBot*);
};