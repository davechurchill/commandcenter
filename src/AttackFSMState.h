#pragma once
#include "sc2api/sc2_api.h"
#include "KitingFSM.h"

class AttackFSMState : public KitingFSMState
{
private:
    const sc2::Unit * m_unit;
    const sc2::Unit * m_target;
    sc2::Point2D m_position;
    std::vector<KitingFSMTransition*> transitions;
public:
    AttackFSMState(const sc2::Unit * unit, const sc2::Unit * target);
    void onEnter();
    void onUpdate(const sc2::Unit * target, CCBot*);
    void onExit();
    std::vector<KitingFSMTransition*> getTransitions();
};