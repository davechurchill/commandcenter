#pragma once
#include "sc2api/sc2_api.h"
#include "FocusFireFSM.h"

class ShouldPullBackTransition : public FocusFireFSMTransition
{
private:
    FocusFireFSMState* m_nextState;
    const sc2::Unit * m_unit;

public:
    ShouldPullBackTransition(const sc2::Unit * unit, FocusFireFSMState* nextState);
    bool isValid(const sc2::Unit * target, const std::vector<const sc2::Unit*> * units, std::unordered_map<sc2::Tag, float> *, CCBot*);
    FocusFireFSMState* getNextState();
    void onTransition();
};