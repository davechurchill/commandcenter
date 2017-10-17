#pragma once
#include "sc2api/sc2_api.h"
#include "FiniteStateMachine.h"
class PullBackFSMState : public CCFSMState
{
private:
    const sc2::Unit * m_unit;
    const sc2::Unit * m_target;
    const std::vector<const sc2::Unit *> * m_units;
    sc2::Point2D m_position;
    std::vector<CCFSMTransition*> transitions;
public:
    PullBackFSMState(const sc2::Unit * unit, const std::vector<const sc2::Unit *> * m_units, const sc2::Unit * target);
    void onEnter();
    void onUpdate(const sc2::Unit * target, CCBot*);
    void onExit();
    std::vector<CCFSMTransition*> getTransitions();
};