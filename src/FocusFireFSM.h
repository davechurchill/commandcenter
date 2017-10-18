#pragma once
#include "FiniteStateMachine.h"

class FocusFireFSMTransition;
class FocusFireFSMState : public FSMState
{
public:
    virtual void onUpdate(const sc2::Unit * m_target, CCBot*);
    virtual std::vector<FocusFireFSMTransition*> getTransitions();
};

class FocusFireFSMTransition : public FSMTransition
{
public:
    virtual FocusFireFSMState* getNextState();
    virtual bool isValid(sc2::Point2D);
};

class FocusFireFiniteStateMachine
{
public:
    virtual void update(const sc2::Unit * target, sc2::Point2D, CCBot* bot);
};