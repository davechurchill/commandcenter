#pragma once

#include "Common.h"
#include "UnitType.h"

class CCBot;
class Unit;

namespace Util
{
    CCRace          GetRaceFromString(const std::string & str);
    CCTilePosition  GetTilePosition(const CCPosition & pos);
    CCPosition      GetPosition(const CCTilePosition & tile);
    std::string     GetStringFromRace(const CCRace & race);

    bool            UnitCanBuildTypeNow(const Unit & unit, const UnitType & type, CCBot & m_bot);
    UnitType        GetTownHall(const CCRace & race, CCBot & bot);
    UnitType        GetSupplyProvider(const CCRace & race, CCBot & bot);
    CCPosition      CalcCenter(const std::vector<Unit> & units);

    UnitType        GetUnitTypeFromName(const std::string & name, CCBot & bot);
    sc2::UpgradeID  GetUpgradeFromName(const std::string & name, CCBot & bot);

#ifdef SC2API
    sc2::BuffID     GetBuffFromName(const std::string & name, CCBot & bot);
    sc2::AbilityID  GetAbilityFromName(const std::string & name, CCBot & bot);
#endif

    float Dist(const Unit & unit, const CCPosition & p2);
    float Dist(const Unit & unit1, const Unit & unit2);
    float Dist(const CCPosition & p1, const CCPosition & p2);
    float DistSq(const CCPosition & p1, const CCPosition & p2);
    
    // Kevin-provided helper functions

};
