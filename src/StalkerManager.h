#pragma once

#include "Common.h"
#include "MicroManager.h"

class CCBot;

class StalkerManager: public MicroManager
{
public:

    StalkerManager(CCBot & bot);
    void    executeMicro(const std::vector<Unit> & targets);
    void    assignTargets(const std::vector<Unit> & targets);
    int     getAttackPriority(const Unit & stalkerUnit, const Unit & target);
    Unit    getTarget(const Unit & stalkerUnit, const std::vector<Unit> & targets);
};
