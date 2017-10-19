#pragma once

#include "Common.h"
#include "MicroManager.h"

class CCBot;

class MeleeManager: public MicroManager
{

public:

    MeleeManager(CCBot & bot);
    void    executeMicro(const std::vector<CCUnit> & targets);
    void    assignTargets(const std::vector<CCUnit> & targets);
    int     getAttackPriority(CCUnit attacker, CCUnit unit);
    CCUnit getTarget(CCUnit meleeUnit, const std::vector<CCUnit> & targets);
    bool    meleeUnitShouldRetreat(CCUnit meleeUnit, const std::vector<CCUnit> & targets);
};
