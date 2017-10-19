#pragma once

#include "BotAssert.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <set>
#include <fstream>
#include <streambuf>
#include <string>

typedef uint64_t UnitTag;

#define SC2API

#ifdef SC2API
    #include "sc2api/sc2_api.h"
    typedef const sc2::Unit *   CCUnit;
    typedef sc2::UnitTypeID     CCUnitType;
#else
    #include "BWAPI.h"
    typedef BWAPI::Unit CCUnit;
    typedef BWAPI::UnitType CCUnitType;
#endif


namespace Players
{
    enum {Self = 0, Enemy = 1, Neutral = 2, Size = 3};
}