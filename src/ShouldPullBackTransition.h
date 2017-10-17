#pragma once
#include "sc2api/sc2_api.h"
#include "FiniteStateMachine.h"

class ShouldPullBackTransition : public CCFSMTransition
{
private:
    CCFSMState* m_nextState;
    const sc2::Unit * m_unit;
    const sc2::Unit * m_target;
    const std::vector<const sc2::Unit *> * m_units;

public:
    ShouldPullBackTransition(const sc2::Unit * unit, const std::vector<const sc2::Unit *> * units, const sc2::Unit * target, CCFSMState* nextState);
    bool isValid();
    CCFSMState* getNextState();
    void onTransition();
};