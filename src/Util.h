#pragma once

#include "sc2api/sc2_api.h"
#include "Common.h"

class CCBot;

namespace Util
{
    struct IsUnit 
    {
        sc2::UNIT_TYPEID m_type;

        IsUnit(sc2::UNIT_TYPEID type);
        bool operator()(const sc2::Unit& unit, const sc2::ObservationInterface*);
    };

    int GetPlayer(const sc2::Unit & unit);
    bool IsCombatUnit(const sc2::Unit & unit, CCBot & bot);
    bool IsCombatUnitType(const sc2::UnitTypeID & type, CCBot & bot);
    bool IsSupplyProvider(const sc2::Unit & unit);
    bool IsSupplyProviderType(const sc2::UnitTypeID & type);
    bool IsTownHall(const sc2::Unit & unit);
    bool IsTownHallType(const sc2::UnitTypeID & type);
    bool IsRefinery(const sc2::Unit & unit);
    bool IsRefineryType(const sc2::UnitTypeID & type);
    bool IsDetector(const sc2::Unit & type);
    bool IsDetectorType(const sc2::UnitTypeID & type);
    bool IsGeyser(const sc2::Unit & unit);
    bool IsMineral(const sc2::Unit & unit);
    bool IsWorker(const sc2::Unit & unit);
    bool IsWorkerType(const sc2::UnitTypeID & unit);
    bool IsIdle(const sc2::Unit & unit);
    bool IsCompleted(const sc2::Unit & unit);
    float GetAttackRange(const sc2::UnitTypeID & type, CCBot & bot);
    
    bool UnitCanBuildTypeNow(const sc2::Unit & unit, const sc2::UnitTypeID & type, CCBot & m_bot);
    int GetUnitTypeWidth(const sc2::UnitTypeID type, const CCBot & bot);
    int GetUnitTypeHeight(const sc2::UnitTypeID type, const CCBot & bot);
    int GetUnitTypeMineralPrice(const sc2::UnitTypeID type, const CCBot & bot);
    int GetUnitTypeGasPrice(const sc2::UnitTypeID type, const CCBot & bot);
    sc2::UnitTypeID GetTownHall(const sc2::Race & race);
    sc2::UnitTypeID GetSupplyProvider(const sc2::Race & race);
    std::string     GetStringFromRace(const sc2::Race & race);
    sc2::Race       GetRaceFromString(const std::string & race);
    sc2::Point2D    CalcCenter(const std::vector<sc2::Unit> & units);

    sc2::UnitTypeID GetUnitTypeIDFromName(const std::string & name, CCBot & bot);
    sc2::UpgradeID  GetUpgradeIDFromName(const std::string & name, CCBot & bot);
    sc2::BuffID     GetBuffIDFromName(const std::string & name, CCBot & bot);
    sc2::AbilityID  GetAbilityIDFromName(const std::string & name, CCBot & bot);

    float Dist(const sc2::Point2D & p1, const sc2::Point2D & p2);
    float DistSq(const sc2::Point2D & p1, const sc2::Point2D & p2);
    
    // Kevin-provided helper functions
    void    VisualizeGrids(const sc2::ObservationInterface* obs, sc2::DebugInterface* debug);
    float   TerainHeight(const sc2::GameInfo& info, const sc2::Point2D& point);
    bool    Placement(const sc2::GameInfo& info, const sc2::Point2D& point);
    bool    Pathable(const sc2::GameInfo& info, const sc2::Point2D& point);

};
