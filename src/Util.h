#pragma once

#include "Common.h"

class CCBot;
class Unit;

namespace Util
{
    CCRace      GetRaceFromString(const std::string & str);
    CCTilePosition GetTilePosition(const CCPosition & pos);
    CCPosition GetPosition(const CCTilePosition & tile);
    std::string GetStringFromRace(const CCRace & race);

    bool IsCombatUnit(const Unit & unit, CCBot & bot);
    bool IsCombatUnitType(const CCUnitType & type, CCBot & bot);
    bool IsSupplyProvider(const Unit & unit);
    bool IsSupplyProviderType(const CCUnitType & type);
    bool IsTownHall(const Unit & unit);
    bool IsTownHallType(const CCUnitType & type);
    bool IsRefinery(const Unit & unit);
    bool IsRefineryType(const CCUnitType & type);
    bool IsDetector(const Unit & type);
    bool IsDetectorType(const CCUnitType & type);
    bool IsGeyser(const Unit & unit);
    bool IsGeyserType(const CCUnitType & type);
    bool IsMineral(const Unit & unit);
    bool IsMineralType(const CCUnitType & type);
    bool IsWorker(const Unit & unit);
    bool IsWorkerType(const CCUnitType & unit);
    float GetAttackRange(const CCUnitType & type, CCBot & bot);
    
    bool UnitCanBuildTypeNow(const Unit & unit, const CCUnitType & type, CCBot & m_bot);
    int GetUnitTypeWidth(const CCUnitType type, const CCBot & bot);
    int GetUnitTypeHeight(const CCUnitType type, const CCBot & bot);
    CCUnitType GetTownHall(const CCRace & race);
    CCUnitType GetSupplyProvider(const CCRace & race);
    CCPosition CalcCenter(const std::vector<CCUnit> & units);

    std::string     GetNameFromUnitType(const CCUnitType & type);
    CCUnitType      GetUnitTypeFromName(const std::string & name, CCBot & bot);
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
