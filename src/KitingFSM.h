#pragma once
#include "FiniteStateMachine.h"

class KitingFSMTransition;
class KitingFSMState : public FSMState
{
public:
    virtual void onUpdate(const sc2::Unit * m_target, CCBot*) { };
    virtual std::vector<KitingFSMTransition*> getTransitions() { return std::vector<KitingFSMTransition*>(); };
};

class KitingFSMTransition : public FSMTransition
{
public:
    virtual KitingFSMState* getNextState() { return nullptr; };
    virtual bool isValid(const sc2::Unit * target, CCBot * bot) { return false; };
};