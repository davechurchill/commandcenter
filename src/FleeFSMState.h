#pragma once
#include "sc2api/sc2_api.h"
#include "KitingFSM.h"
class FleeFSMState : public KitingFSMState
{
private:
    const sc2::Unit * m_unit;
    const sc2::Unit * m_target;
    const std::vector<const sc2::Unit *> * m_units;
    sc2::Point2D m_position;
    std::vector<KitingFSMTransition*> transitions;
public:
    FleeFSMState(const sc2::Unit * unit, const sc2::Unit * target);
    void onEnter();
    void onUpdate(const sc2::Unit * target, CCBot*);
    void onExit();
    std::vector<KitingFSMTransition*> getTransitions();
};