#pragma once

#include "Common.h"
#include "MicroManager.h"

class CCBot;

class RangedManager: public MicroManager
{
public:

    RangedManager(CCBot & bot);
    void    executeMicro(const std::vector<CCUnit> & targets);
    void    assignTargets(const std::vector<CCUnit> & targets);
    int     getAttackPriority(CCUnit rangedUnit, CCUnit target);
    CCUnit getTarget(CCUnit rangedUnit, const std::vector<CCUnit> & targets);
};
