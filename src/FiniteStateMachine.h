#pragma once
#include <vector>
#include "sc2api/sc2_api.h"
class CCBot;

class FSMTransition;

class FSMState
{
public:
    virtual void onEnter();
    virtual void onUpdate();
    virtual void onExit();
};

class FSMTransition
{
public:
    virtual bool isValid();
    virtual FSMState* getNextState();
    virtual void onTransition();
};

class CCFSMTransition;
class CCFSMState : public FSMState
{
public:
    virtual void onUpdate(const sc2::Unit * m_target, CCBot*);
    virtual std::vector<CCFSMTransition*> getTransitions();
};

class CCFSMTransition : public FSMTransition
{
public:
    virtual CCFSMState* getNextState();
};

class CCFiniteStateMachine
{
public:
    virtual void update(const sc2::Unit * target, CCBot* bot);
};