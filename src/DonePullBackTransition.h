#pragma once
#include "sc2api/sc2_api.h"
#include "FiniteStateMachine.h"

class DonePullBackTransition : public FocusFireFSMTransition
{
private:
    FocusFireFSMState* m_nextState;
    const sc2::Unit* m_unit;
    sc2::Point2D m_position;
public:
    DonePullBackTransition(const sc2::Unit * rangedUnit, sc2::Point2D position, FocusFireFSMState* nextState);
    bool isValid(sc2::Point2D position);
    FocusFireFSMState* getNextState();
    void onTransition();
};