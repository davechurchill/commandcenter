#pragma once

#include "BotAssert.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <set>
#include <fstream>
#include <streambuf>
#include <string>
#include <array>

#define SC2API

#ifdef SC2API
    #include "sc2api/sc2_api.h"
    //typedef const sc2::Unit *   CCUnit;
    typedef sc2::UnitTypeID     CCUnitType;
    typedef sc2::Point2D        CCPosition;
    typedef sc2::Point2DI       CCTilePosition;
    typedef float               CCPositionType;
    typedef sc2::Color          CCColor;
    typedef sc2::Tag            CCUnitID;
    typedef sc2::Race           CCRace;
    typedef float               CCHealth;
    
#else
    #include "BWAPI.h"
    //typedef BWAPI::Unit         CCUnit;
    typedef BWAPI::UnitType     CCUnitType;
    typedef BWAPI::Position     CCPosition;
    typedef BWAPI::TilePosition CCTilePosition;
    typedef int                 CCPositionType;
    typedef BWAPI::Color        CCColor;
    typedef BWAPI::Race         CCRace;
    typedef int                 CCUnitID;
    typedef int                 CCHealth;
#endif
    
typedef size_t CCPlayer;
namespace Players
{
    enum {Self = 0u, Enemy = 1u, Neutral = 2u, Size = 3u};
}