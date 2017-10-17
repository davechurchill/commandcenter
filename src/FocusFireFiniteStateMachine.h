#pragma once
#include "sc2api/sc2_api.h"
#include "FiniteStateMachine.h"
class CCBot;
class FocusFireClosestFSMState : public FSMState
{
private:
    const sc2::Unit* m_unit;
    const sc2::Unit* m_target;
    CCBot* m_bot;
public:
    FocusFireClosestFSMState(const sc2::Unit* unit, const sc2::Unit* target, CCBot* bot);
    virtual void onEnter();
    virtual void onUpdate();
    virtual void onExit();
    std::vector<FSMTransition> transitions;
};

class PullBackFSMState : public FSMState
{
private:
    const sc2::Unit* m_unit;
    const sc2::Unit* m_target;
    CCBot* m_bot;
public:
    virtual void onEnter();
    virtual void onUpdate();
    virtual void onExit();
    std::vector<FSMTransition> transitions;
};

class ShouldPullBackTransition : public FSMTransition
{
private:
    FSMState* m_nextState;
public:
    virtual bool isValid();
    virtual FSMState* getNextState();
    virtual void onTransition();
};

class DonePullBackTransition : public virtual FSMTransition
{
private:
    FSMState* m_nextState;
public:
    virtual bool isValid();
    virtual FSMState* getNextState();
    virtual void onTransition();
};