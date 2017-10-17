#pragma once
#include "FocusFireFiniteStateMachine.h"

class FocusFireClosestFSMState : public FSMState
{
private:
    const sc2::Unit* m_unit;
    const sc2::Unit* m_target;
    CCBot* m_bot;
public:
    FocusFireClosestFSMState(const sc2::Unit* unit, const sc2::Unit* target, CCBot* bot)
    {
        m_unit = unit;
        m_target = target;
        m_bot = bot;
    }

    void onEnter() {}
    void onExit() {}
    void onUpdate() 
    {
        // fire
    }
};

class PullBackFSMState : public FSMState
{
private:
    const sc2::Unit* m_unit;
    sc2::Point2D m_position;
    CCBot* m_bot;
public:
    PullBackFSMState(const sc2::Unit* unit, sc2::Point2D position, CCBot* bot)
    {
        m_unit = unit;
        m_position = position;
        m_bot = bot;
    }

    void onEnter() {}
    void onExit() {}
    void onUpdate()
    {
        // run
    }
};

class ShouldPullBackTransition : public FSMTransition
{
private:
    FSMState* m_nextState;
public:
    ShouldPullBackTransition() {}

    bool isValid() 
    {
        // verify stuff here
    }
    FSMState* getNextState()
    {
        return m_nextState;
    }

    void onTransition() { }
};

class DonePullBackTransition : public virtual FSMTransition
{
private:
    FSMState* m_nextState;
public:
    DonePullBackTransition() {}

    bool isValid()
    {
        // verify stuff here
    }
    FSMState* getNextState()
    {
        return m_nextState;
    }

    void onTransition() { }
};