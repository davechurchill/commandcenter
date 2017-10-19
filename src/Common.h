#pragma once

#include "BotAssert.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <set>
#include <fstream>
#include <streambuf>
#include <string>

#define SC2API

#ifdef SC2API
    #include "sc2api/sc2_api.h"
    typedef const sc2::Unit *   CCUnit;
    typedef sc2::UnitTypeID     CCUnitType;
    typedef sc2::Point2D        CCPosition;
    typedef sc2::Color          CCColor;
    typedef sc2::Tag            CCUnitID;
    
#else
    #include "BWAPI.h"
    typedef BWAPI::Unit         CCUnit;
    typedef BWAPI::UnitType     CCUnitType;
    typedef BWAPI::Position     CCPosition;
    typedef BWAPI::Color        CCColor;
    typedef int                 CCUnitID;
#endif


namespace Players
{
    enum {Self = 0, Enemy = 1, Neutral = 2, Size = 3};
}