#pragma once
#include "sc2api/sc2_api.h"
#include "FocusFireFSM.h"

class ShouldPullBackTransition : public FocusFireFSMTransition
{
private:
    FocusFireFSMState* m_nextState;
    const sc2::Unit * m_unit;
    const sc2::Unit * m_target;
    const std::vector<const sc2::Unit *> * m_units;

public:
    ShouldPullBackTransition(const sc2::Unit * unit, const std::vector<const sc2::Unit *> * units, const sc2::Unit * target, FocusFireFSMState* nextState);
    bool isValid(sc2::Point2D);
    FocusFireFSMState* getNextState();
    void onTransition();
};