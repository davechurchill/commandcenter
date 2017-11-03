#pragma once
#include "FiniteStateMachine.h"

class FocusFireFSMTransition;
class FocusFireFSMState : public FSMState
{
public:
    virtual void onUpdate(const sc2::Unit * m_target, CCBot*) { };
    virtual void onEnter(const std::vector<const sc2::Unit*> *, CCBot*) { };
    virtual std::vector<FocusFireFSMTransition*> getTransitions() { return std::vector<FocusFireFSMTransition*>(); };
};

class FocusFireFSMTransition : public FSMTransition
{
public:
    virtual FocusFireFSMState* getNextState() { return nullptr; };
    virtual bool isValid(const sc2::Unit * target, const std::vector<const sc2::Unit*> *units, std::unordered_map<sc2::Tag, float> *, CCBot*) { return false; };
};