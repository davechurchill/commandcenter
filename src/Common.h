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
#include "json/json.hpp"

using json = nlohmann::json;

#ifdef SC2API
    #include "sc2api/sc2_api.h"
    typedef sc2::Point2D        CCPosition;
    typedef sc2::Point2DI       CCTilePosition;
    typedef sc2::Color          CCColor;
    typedef sc2::UpgradeID      CCUpgrade;
    typedef sc2::Tag            CCUnitID;
    typedef sc2::Race           CCRace;
    typedef float               CCHealth;
    typedef float               CCPositionType;
    
#else
    #include "BWAPI.h"
    typedef BWAPI::Position     CCPosition;
    typedef BWAPI::TilePosition CCTilePosition;
    typedef BWAPI::Color        CCColor;
    typedef BWAPI::Race         CCRace;
    typedef BWAPI::UpgradeType  CCUpgrade;
    typedef int                 CCUnitID;
    typedef int                 CCHealth;
    typedef int                 CCPositionType;
#endif
    
typedef size_t CCPlayer;
namespace Players
{
    enum {Self = 0u, Enemy = 1u, Neutral = 2u, Size = 3u, None = 4u};
}