#pragma once

#include "Common.h"

class CCBot;

namespace Util
{
    int GetPlayer(CCUnit unit);
    CCUnitType GetType(CCUnit unit);
    CCUnitID GetID(CCUnit unit);

    bool IsCombatUnit(CCUnit unit, CCBot & bot);
    bool IsCombatUnitType(const CCUnitType & type, CCBot & bot);
    bool IsSupplyProvider(CCUnit unit);
    bool IsSupplyProviderType(const CCUnitType & type);
    bool IsTownHall(CCUnit unit);
    bool IsTownHallType(const CCUnitType & type);
    bool IsRefinery(CCUnit unit);
    bool IsRefineryType(const CCUnitType & type);
    bool IsDetector(CCUnit type);
    bool IsDetectorType(const CCUnitType & type);
    bool IsGeyser(CCUnit unit);
    bool IsGeyserType(const CCUnitType & type);
    bool IsMineral(CCUnit unit);
    bool IsMineralType(const CCUnitType & type);
    bool IsWorker(CCUnit unit);
    bool IsWorkerType(const CCUnitType & unit);
    bool IsIdle(CCUnit unit);
    bool IsCompleted(CCUnit unit);
    float GetAttackRange(const CCUnitType & type, CCBot & bot);
    
    bool UnitCanBuildTypeNow(CCUnit unit, const CCUnitType & type, CCBot & m_bot);
    int GetUnitTypeWidth(const CCUnitType type, const CCBot & bot);
    int GetUnitTypeHeight(const CCUnitType type, const CCBot & bot);
    int GetUnitTypeMineralPrice(const CCUnitType type, const CCBot & bot);
    int GetUnitTypeGasPrice(const CCUnitType type, const CCBot & bot);
    CCUnitType GetTownHall(const sc2::Race & race);
    CCUnitType GetSupplyProvider(const sc2::Race & race);
    std::string     GetStringFromRace(const sc2::Race & race);
    sc2::Race       GetRaceFromString(const std::string & race);
    CCPosition    CalcCenter(const std::vector<CCUnit> & units);

    CCUnitType GetUnitTypeFromName(const std::string & name, CCBot & bot);
    sc2::UpgradeID  GetUpgradeFromName(const std::string & name, CCBot & bot);

#ifdef SC2API
    sc2::BuffID     GetBuffFromName(const std::string & name, CCBot & bot);
    sc2::AbilityID  GetAbilityFromName(const std::string & name, CCBot & bot);
#endif

    float Dist(const CCPosition & p1, const CCPosition & p2);
    float DistSq(const CCPosition & p1, const CCPosition & p2);
    
    // Kevin-provided helper functions

};
