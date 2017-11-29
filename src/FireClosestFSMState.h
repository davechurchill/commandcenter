#pragma once
#include "sc2api/sc2_api.h"
#include "FocusFireFSM.h"

class FireClosestFSMState : public FocusFireFSMState
{
private:
    const sc2::Unit * m_unit;
    const sc2::Unit * m_target;
    std::vector<FocusFireFSMTransition*> transitions;
public:
    FireClosestFSMState(const sc2::Unit * unit);
    void onEnter(const std::vector<const sc2::Unit*> *, CCBot*);
    void onUpdate(const sc2::Unit * target, CCBot*);
    void onExit();
    std::vector<FocusFireFSMTransition*> getTransitions();
};