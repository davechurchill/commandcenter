#pragma once
#include "sc2api/sc2_api.h"
#include "KitingFSM.h"

class ShouldAttackTransition : public KitingFSMTransition
{
private:
    KitingFSMState* m_nextState;
    const sc2::Unit * m_unit;
    const sc2::Unit * m_target;

public:
    ShouldAttackTransition(const sc2::Unit * unit, const sc2::Unit * target, KitingFSMState* nextState);
    bool isValid(const sc2::Unit * target, CCBot * bot);
    KitingFSMState* getNextState();
    void onTransition();
};