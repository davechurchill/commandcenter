#pragma once
#include "sc2api/sc2_api.h"
#include "FocusFireFSM.h"

class DonePullBackTransition : public FocusFireFSMTransition
{
private:
    FocusFireFSMState* m_nextState;
    const sc2::Unit* m_unit;
    sc2::Point2D m_position;
public:
    DonePullBackTransition(const sc2::Unit * rangedUnit, sc2::Point2D position, FocusFireFSMState* nextState);
    bool isValid(const std::vector<const sc2::Unit*> * units, std::unordered_map<sc2::Tag, float> *, CCBot*);
    FocusFireFSMState* getNextState();
    void onTransition();
};