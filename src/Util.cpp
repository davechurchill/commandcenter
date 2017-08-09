#include "sc2api/sc2_api.h"
#include "sc2utils/sc2_manage_process.h"
#include "Util.h"
#include "CCBot.h"
#include <iostream>

Util::IsUnit::IsUnit(sc2::UNIT_TYPEID type) 
    : m_type(type) 
{
}
 
bool Util::IsUnit::operator()(const sc2::Unit& unit, const sc2::ObservationInterface*) 
{ 
    return unit.unit_type == m_type; 
};

bool Util::IsTownHallType(const sc2::UnitTypeID & type)
{
    switch (type.ToType()) 
    {
        case sc2::UNIT_TYPEID::ZERG_HATCHERY                : return true;
        case sc2::UNIT_TYPEID::ZERG_LAIR                    : return true;
        case sc2::UNIT_TYPEID::ZERG_HIVE                    : return true;
        case sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER         : return true;
        case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND        : return true;
        case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING  : return true;
        case sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS     : return true;
        case sc2::UNIT_TYPEID::PROTOSS_NEXUS                : return true;
        default: return false;
    }
}

bool Util::IsTownHall(const sc2::Unit & unit)
{
    return IsTownHallType(unit.unit_type);
}

bool Util::IsRefinery(const sc2::Unit & unit)
{
    return IsRefineryType(unit.unit_type);
}

bool Util::IsRefineryType(const sc2::UnitTypeID & type)
{
    switch (type.ToType()) 
    {
        case sc2::UNIT_TYPEID::TERRAN_REFINERY      : return true;
        case sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR  : return true;
        case sc2::UNIT_TYPEID::ZERG_EXTRACTOR       : return true;
        default: return false;
    }
}

bool Util::IsGeyser(const sc2::Unit & unit)
{
    switch (unit.unit_type.ToType()) 
    {
        case sc2::UNIT_TYPEID::NEUTRAL_VESPENEGEYSER        : return true;
        case sc2::UNIT_TYPEID::NEUTRAL_PROTOSSVESPENEGEYSER : return true;
        case sc2::UNIT_TYPEID::NEUTRAL_SPACEPLATFORMGEYSER  : return true;
        default: return false;
    }
}

bool Util::IsMineral(const sc2::Unit & unit)
{
    switch (unit.unit_type.ToType()) 
    {
        case sc2::UNIT_TYPEID::NEUTRAL_MINERALFIELD         : return true;
        case sc2::UNIT_TYPEID::NEUTRAL_MINERALFIELD750      : return true;
        case sc2::UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD     : return true;
        case sc2::UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD750  : return true;
        default: return false;
    }
}

bool Util::IsWorker(const sc2::Unit & unit)
{
    return IsWorkerType(unit.unit_type);
}

bool Util::IsWorkerType(const sc2::UnitTypeID & unit)
{
    switch (unit.ToType()) 
    {
        case sc2::UNIT_TYPEID::TERRAN_SCV           : return true;
        case sc2::UNIT_TYPEID::PROTOSS_PROBE        : return true;
        case sc2::UNIT_TYPEID::ZERG_DRONE           : return true;
        case sc2::UNIT_TYPEID::ZERG_DRONEBURROWED   : return true;
        default: return false;
    }
}

sc2::UnitTypeID Util::GetSupplyProvider(const sc2::Race & race)
{
    switch (race) 
    {
        case sc2::Race::Terran: return sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT;
        case sc2::Race::Protoss: return sc2::UNIT_TYPEID::PROTOSS_PYLON;
        case sc2::Race::Zerg: return sc2::UNIT_TYPEID::ZERG_OVERLORD;
        default: return 0;
    }
}

sc2::UnitTypeID Util::GetTownHall(const sc2::Race & race)
{
    switch (race) 
    {
        case sc2::Race::Terran: return sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER;
        case sc2::Race::Protoss: return sc2::UNIT_TYPEID::PROTOSS_NEXUS;
        case sc2::Race::Zerg: return sc2::UNIT_TYPEID::ZERG_HATCHERY;
        default: return 0;
    }
}

bool Util::IsCompleted(const sc2::Unit & unit)
{
    return unit.build_progress == 1.0f;
}

bool Util::IsIdle(const sc2::Unit & unit)
{
    return unit.orders.empty();
}

int Util::GetUnitTypeMineralPrice(const sc2::UnitTypeID type, const CCBot & bot)
{
    return bot.Observation()->GetUnitTypeData()[type].mineral_cost;
}

int Util::GetUnitTypeGasPrice(const sc2::UnitTypeID type, const CCBot & bot)
{
    return bot.Observation()->GetUnitTypeData()[type].vespene_cost;
}

int Util::GetUnitTypeWidth(const sc2::UnitTypeID type, const CCBot & bot)
{
    return (int)(2 * bot.Observation()->GetAbilityData()[UnitTypeIDToAbilityID(type)].footprint_radius);
}

int Util::GetUnitTypeHeight(const sc2::UnitTypeID type, const CCBot & bot)
{
    return (int)(2 * bot.Observation()->GetAbilityData()[UnitTypeIDToAbilityID(type)].footprint_radius);
}


sc2::Point2D Util::CalcCenter(const std::vector<sc2::Unit> & units)
{
    if (units.empty())
    {
        return sc2::Point2D(0.0f,0.0f);
    }

    float cx = 0.0f;
    float cy = 0.0f;

    for (auto & unit : units)
    {
        cx += unit.pos.x;
        cy += unit.pos.y;
    }

    return sc2::Point2D(cx / units.size(), cy / units.size());
}

bool Util::IsDetector(const sc2::Unit & unit)
{
    return IsDetectorType(unit.unit_type);
}

float Util::GetAttackRange(const sc2::UnitTypeID & type, CCBot & bot)
{
    auto & weapons = bot.Observation()->GetUnitTypeData()[type].weapons;
    
    if (weapons.empty())
    {
        return 0.0f;
    }

    float maxRange = 0.0f;
    for (auto & weapon : weapons)
    {
        if (weapon.range > maxRange)
        {
            maxRange = weapon.range;
        }
    }

    return maxRange;
}

// TODO: implement
bool Util::IsDetectorType(const sc2::UnitTypeID & type)
{
    return false;
}

int Util::GetPlayer(const sc2::Unit & unit)
{
    if (unit.alliance == sc2::Unit::Alliance::Self)
    {
        return 0;
    }

    if (unit.alliance == sc2::Unit::Alliance::Enemy)
    {
        return 1;
    }

    if (unit.alliance == sc2::Unit::Alliance::Neutral)
    {
        return 2;
    }

    return -1;
}

bool Util::IsCombatUnitType(const sc2::UnitTypeID type)
{
    if (IsWorkerType(type)) { return false; }
    if (IsSupplyProviderType(type)) { return false; }
    if (IsBuilding(type)) { return false; }

    if (type == sc2::UNIT_TYPEID::ZERG_EGG) { return false; }
    if (type == sc2::UNIT_TYPEID::ZERG_LARVA) { return false; }

    return true;
}

bool Util::IsCombatUnit(const sc2::Unit & unit)
{
    return IsCombatUnitType(unit.unit_type);
}

bool Util::IsSupplyProviderType(const sc2::UnitTypeID type)
{
    switch (type.ToType()) 
    {
        case sc2::UNIT_TYPEID::ZERG_OVERLORD                : return true;
        case sc2::UNIT_TYPEID::PROTOSS_PYLON                : return true;
        case sc2::UNIT_TYPEID::PROTOSS_PYLONOVERCHARGED     : return true;
        case sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT           : return true;
        case sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOTLOWERED    : return true;
        default: return false;
    }

    return true;
}

bool Util::IsSupplyProvider(const sc2::Unit & unit)
{
    return IsSupplyProviderType(unit.unit_type);
}

float Util::Dist(const sc2::Point2D & p1, const sc2::Point2D & p2)
{
    return sqrtf(Util::DistSq(p1,p2));
}

float Util::DistSq(const sc2::Point2D & p1, const sc2::Point2D & p2)
{
    float dx = p1.x - p2.x;
    float dy = p1.y - p2.y;

    return dx*dx + dy*dy;
}

bool Util::Pathable(const sc2::GameInfo & info, const sc2::Point2D & point) 
{
    sc2::Point2DI pointI((int)point.x, (int)point.y);
    if (pointI.x < 0 || pointI.x >= info.width || pointI.y < 0 || pointI.y >= info.width)
    {
        return false;
    }

    assert(info.pathing_grid.data.size() == info.width * info.height);
    unsigned char encodedPlacement = info.pathing_grid.data[pointI.x + ((info.height - 1) - pointI.y) * info.width];
    bool decodedPlacement = encodedPlacement == 255 ? false : true;
    return decodedPlacement;
}

bool Util::Placement(const sc2::GameInfo & info, const sc2::Point2D & point) 
{
    sc2::Point2DI pointI((int)point.x, (int)point.y);
    if (pointI.x < 0 || pointI.x >= info.width || pointI.y < 0 || pointI.y >= info.width)
    {
        return false;
    }

    assert(info.placement_grid.data.size() == info.width * info.height);
    unsigned char encodedPlacement = info.placement_grid.data[pointI.x + ((info.height - 1) - pointI.y) * info.width];
    bool decodedPlacement = encodedPlacement == 255 ? true : false;
    return decodedPlacement;
}

float Util::TerainHeight(const sc2::GameInfo & info, const sc2::Point2D & point) 
{
    sc2::Point2DI pointI((int)point.x, (int)point.y);
    if (pointI.x < 0 || pointI.x >= info.width || pointI.y < 0 || pointI.y >= info.width)
    {
        return 0.0f;
    }

    assert(info.terrain_height.data.size() == info.width * info.height);
    unsigned char encodedHeight = info.terrain_height.data[pointI.x + ((info.height - 1) - pointI.y) * info.width];
    float decodedHeight = -100.0f + 200.0f * float(encodedHeight) / 255.0f;
    return decodedHeight;
}

void Util::VisualizeGrids(const sc2::ObservationInterface * obs, sc2::DebugInterface * debug) 
{
    const sc2::GameInfo& info = obs->GetGameInfo();

    sc2::Point2D camera = obs->GetCameraPos();
    for (float x = camera.x - 8.0f; x < camera.x + 8.0f; ++x) 
    {
        for (float y = camera.y - 8.0f; y < camera.y + 8.0f; ++y) 
        {
            // Draw in the center of each 1x1 cell
            sc2::Point2D point(x + 0.5f, y + 0.5f);

            float height = TerainHeight(info, sc2::Point2D(x, y));
            bool placable = Placement(info, sc2::Point2D(x, y));
            //bool pathable = Pathable(info, sc2::Point2D(x, y));

            sc2::Color color = placable ? sc2::Colors::Green : sc2::Colors::Red;
            debug->DebugSphereOut(sc2::Point3D(point.x, point.y, height + 0.5f), 0.4f, color);
        }
    }

    debug->SendDebug();
}

std::string Util::GetStringFromRace(const sc2::Race & race)
{
    if (race == sc2::Race::Terran)
    {
        return "Terran";
    }
    else if (race == sc2::Race::Protoss)
    {
        return "Protoss";
    }
    else
    {
        return "Zerg";
    }
}

sc2::Race Util::GetRaceFromString(const std::string & race)
{
    if (race == "Terran")
    {
        return sc2::Race::Terran;
    }
    else if (race == "Protoss")
    {
        return sc2::Race::Protoss;
    }
    else if (race == "Zerg")
    {
        return sc2::Race::Zerg;
    }

    BOT_ASSERT(false, "Unknown Race: ", race.c_str());
    return sc2::Race::Terran;
}

sc2::UnitTypeID Util::WhatBuilds(const sc2::UnitTypeID & type)
{
    switch (type.ToType()) 
    {
        case sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR:         return sc2::UNIT_TYPEID::PROTOSS_PROBE; 
        case sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE:     return sc2::UNIT_TYPEID::PROTOSS_PROBE; 
        case sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE:          return sc2::UNIT_TYPEID::PROTOSS_PROBE; 
        case sc2::UNIT_TYPEID::PROTOSS_PYLON:               return sc2::UNIT_TYPEID::PROTOSS_PROBE; 
        case sc2::UNIT_TYPEID::PROTOSS_NEXUS:               return sc2::UNIT_TYPEID::PROTOSS_PROBE; 
        case sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON:         return sc2::UNIT_TYPEID::PROTOSS_PROBE; 
        case sc2::UNIT_TYPEID::PROTOSS_FORGE:               return sc2::UNIT_TYPEID::PROTOSS_PROBE; 
        case sc2::UNIT_TYPEID::PROTOSS_GATEWAY:             return sc2::UNIT_TYPEID::PROTOSS_PROBE;  
        case sc2::UNIT_TYPEID::PROTOSS_STARGATE:            return sc2::UNIT_TYPEID::PROTOSS_PROBE; 
        case sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON:        return sc2::UNIT_TYPEID::PROTOSS_PROBE; 
        case sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY:         return sc2::UNIT_TYPEID::PROTOSS_PROBE; 
        case sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY:    return sc2::UNIT_TYPEID::PROTOSS_PROBE; 
        case sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE:      return sc2::UNIT_TYPEID::PROTOSS_PROBE; 
        case sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL:     return sc2::UNIT_TYPEID::PROTOSS_PROBE; 
        case sc2::UNIT_TYPEID::PROTOSS_PROBE:               return sc2::UNIT_TYPEID::PROTOSS_NEXUS; 
        case sc2::UNIT_TYPEID::PROTOSS_MOTHERSHIPCORE:      return sc2::UNIT_TYPEID::PROTOSS_NEXUS; 
        case sc2::UNIT_TYPEID::PROTOSS_ZEALOT:              return sc2::UNIT_TYPEID::PROTOSS_GATEWAY; 
        case sc2::UNIT_TYPEID::PROTOSS_SENTRY:              return sc2::UNIT_TYPEID::PROTOSS_GATEWAY;  
        case sc2::UNIT_TYPEID::PROTOSS_STALKER:             return sc2::UNIT_TYPEID::PROTOSS_GATEWAY; 
        case sc2::UNIT_TYPEID::PROTOSS_HIGHTEMPLAR:         return sc2::UNIT_TYPEID::PROTOSS_GATEWAY; 
        case sc2::UNIT_TYPEID::PROTOSS_DARKTEMPLAR:         return sc2::UNIT_TYPEID::PROTOSS_GATEWAY; 
        case sc2::UNIT_TYPEID::PROTOSS_ADEPT:               return sc2::UNIT_TYPEID::PROTOSS_GATEWAY; 
        case sc2::UNIT_TYPEID::PROTOSS_COLOSSUS:            return sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY; 
        case sc2::UNIT_TYPEID::PROTOSS_DISRUPTOR:           return sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY; 
        case sc2::UNIT_TYPEID::PROTOSS_WARPPRISM:           return sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY; 
        case sc2::UNIT_TYPEID::PROTOSS_OBSERVER:            return sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY;
        case sc2::UNIT_TYPEID::PROTOSS_IMMORTAL:            return sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY;
        case sc2::UNIT_TYPEID::PROTOSS_CARRIER:             return sc2::UNIT_TYPEID::PROTOSS_STARGATE;  
        case sc2::UNIT_TYPEID::PROTOSS_ORACLE:              return sc2::UNIT_TYPEID::PROTOSS_STARGATE; 
        case sc2::UNIT_TYPEID::PROTOSS_PHOENIX:             return sc2::UNIT_TYPEID::PROTOSS_STARGATE; 
        case sc2::UNIT_TYPEID::PROTOSS_VOIDRAY:             return sc2::UNIT_TYPEID::PROTOSS_STARGATE;  
        case sc2::UNIT_TYPEID::PROTOSS_TEMPEST:             return sc2::UNIT_TYPEID::PROTOSS_STARGATE;
        case sc2::UNIT_TYPEID::PROTOSS_INTERCEPTOR:         return sc2::UNIT_TYPEID::PROTOSS_CARRIER; 
        case sc2::UNIT_TYPEID::PROTOSS_ORACLESTASISTRAP:    return sc2::UNIT_TYPEID::PROTOSS_ORACLE; 
        case sc2::UNIT_TYPEID::TERRAN_ARMORY:               return sc2::UNIT_TYPEID::TERRAN_SCV; 
        case sc2::UNIT_TYPEID::TERRAN_BARRACKS:             return sc2::UNIT_TYPEID::TERRAN_SCV; 
        case sc2::UNIT_TYPEID::TERRAN_BARRACKSREACTOR:      return sc2::UNIT_TYPEID::TERRAN_SCV; 
        case sc2::UNIT_TYPEID::TERRAN_REFINERY:             return sc2::UNIT_TYPEID::TERRAN_SCV; 
        case sc2::UNIT_TYPEID::TERRAN_SENSORTOWER:          return sc2::UNIT_TYPEID::TERRAN_SCV; 
        case sc2::UNIT_TYPEID::TERRAN_FACTORY:              return sc2::UNIT_TYPEID::TERRAN_SCV; 
        case sc2::UNIT_TYPEID::TERRAN_FUSIONCORE:           return sc2::UNIT_TYPEID::TERRAN_SCV; 
        case sc2::UNIT_TYPEID::TERRAN_STARPORT:             return sc2::UNIT_TYPEID::TERRAN_SCV; 
        case sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT:          return sc2::UNIT_TYPEID::TERRAN_SCV; 
        case sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY:         return sc2::UNIT_TYPEID::TERRAN_SCV; 
        case sc2::UNIT_TYPEID::TERRAN_BUNKER:               return sc2::UNIT_TYPEID::TERRAN_SCV; 
        case sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER:        return sc2::UNIT_TYPEID::TERRAN_SCV; 
        case sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY:       return sc2::UNIT_TYPEID::TERRAN_SCV; 
        case sc2::UNIT_TYPEID::TERRAN_MISSILETURRET:        return sc2::UNIT_TYPEID::TERRAN_SCV; 
        case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND:       return sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER; 
        case sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS:    return sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER;
        case sc2::UNIT_TYPEID::TERRAN_SCV:                  return sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER; 
        case sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB:      return sc2::UNIT_TYPEID::TERRAN_BARRACKS; 
        case sc2::UNIT_TYPEID::TERRAN_GHOST:                return sc2::UNIT_TYPEID::TERRAN_BARRACKS; 
        case sc2::UNIT_TYPEID::TERRAN_MARAUDER:             return sc2::UNIT_TYPEID::TERRAN_BARRACKS; 
        case sc2::UNIT_TYPEID::TERRAN_MARINE:               return sc2::UNIT_TYPEID::TERRAN_BARRACKS;
        case sc2::UNIT_TYPEID::TERRAN_FACTORYREACTOR:       return sc2::UNIT_TYPEID::TERRAN_FACTORY; 
        case sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB:       return sc2::UNIT_TYPEID::TERRAN_FACTORY; 
        case sc2::UNIT_TYPEID::TERRAN_HELLION:              return sc2::UNIT_TYPEID::TERRAN_FACTORY; 
        case sc2::UNIT_TYPEID::TERRAN_CYCLONE:              return sc2::UNIT_TYPEID::TERRAN_FACTORY;  
        case sc2::UNIT_TYPEID::TERRAN_SIEGETANK:            return sc2::UNIT_TYPEID::TERRAN_FACTORY; 
        case sc2::UNIT_TYPEID::TERRAN_THOR:                 return sc2::UNIT_TYPEID::TERRAN_FACTORY;  
        case sc2::UNIT_TYPEID::TERRAN_WIDOWMINE:            return sc2::UNIT_TYPEID::TERRAN_FACTORY; 
        case sc2::UNIT_TYPEID::TERRAN_NUKE:                 return sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY; 
        case sc2::UNIT_TYPEID::TERRAN_STARPORTREACTOR:      return sc2::UNIT_TYPEID::TERRAN_STARPORT; 
        case sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB:      return sc2::UNIT_TYPEID::TERRAN_STARPORT; 
        case sc2::UNIT_TYPEID::TERRAN_BANSHEE:              return sc2::UNIT_TYPEID::TERRAN_STARPORT; 
        case sc2::UNIT_TYPEID::TERRAN_BATTLECRUISER:        return sc2::UNIT_TYPEID::TERRAN_STARPORT; 
        case sc2::UNIT_TYPEID::TERRAN_LIBERATOR:            return sc2::UNIT_TYPEID::TERRAN_STARPORT; 
        case sc2::UNIT_TYPEID::TERRAN_VIKINGFIGHTER:        return sc2::UNIT_TYPEID::TERRAN_STARPORT; 
        case sc2::UNIT_TYPEID::TERRAN_RAVEN:                return sc2::UNIT_TYPEID::TERRAN_STARPORT; 
        case sc2::UNIT_TYPEID::TERRAN_MEDIVAC:              return sc2::UNIT_TYPEID::TERRAN_STARPORT; 
        case sc2::UNIT_TYPEID::ZERG_HATCHERY:               return sc2::UNIT_TYPEID::ZERG_DRONE; 
        case sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER:       return sc2::UNIT_TYPEID::ZERG_DRONE; 
        case sc2::UNIT_TYPEID::ZERG_EXTRACTOR:              return sc2::UNIT_TYPEID::ZERG_DRONE; 
        case sc2::UNIT_TYPEID::ZERG_BANELINGNEST:           return sc2::UNIT_TYPEID::ZERG_DRONE; 
        case sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN:           return sc2::UNIT_TYPEID::ZERG_DRONE; 
        case sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT:         return sc2::UNIT_TYPEID::ZERG_DRONE; 
        case sc2::UNIT_TYPEID::ZERG_NYDUSCANAL:             return sc2::UNIT_TYPEID::ZERG_DRONE; 
        case sc2::UNIT_TYPEID::ZERG_NYDUSNETWORK:           return sc2::UNIT_TYPEID::ZERG_DRONE; 
        case sc2::UNIT_TYPEID::ZERG_ROACHWARREN:            return sc2::UNIT_TYPEID::ZERG_DRONE; 
        case sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL:           return sc2::UNIT_TYPEID::ZERG_DRONE; 
        case sc2::UNIT_TYPEID::ZERG_SPINECRAWLER:           return sc2::UNIT_TYPEID::ZERG_DRONE; 
        case sc2::UNIT_TYPEID::ZERG_SPIRE:                  return sc2::UNIT_TYPEID::ZERG_DRONE; 
        case sc2::UNIT_TYPEID::ZERG_SPORECRAWLER:           return sc2::UNIT_TYPEID::ZERG_DRONE;
        case sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN:        return sc2::UNIT_TYPEID::ZERG_DRONE; 
        case sc2::UNIT_TYPEID::ZERG_OVERLORD:               return sc2::UNIT_TYPEID::ZERG_LARVA; 
        case sc2::UNIT_TYPEID::ZERG_BANELING:               return sc2::UNIT_TYPEID::ZERG_LARVA; 
        case sc2::UNIT_TYPEID::ZERG_CORRUPTOR:              return sc2::UNIT_TYPEID::ZERG_LARVA;
        case sc2::UNIT_TYPEID::ZERG_DRONE:                  return sc2::UNIT_TYPEID::ZERG_LARVA; 
        case sc2::UNIT_TYPEID::ZERG_HYDRALISK:              return sc2::UNIT_TYPEID::ZERG_LARVA; 
        case sc2::UNIT_TYPEID::ZERG_INFESTOR:               return sc2::UNIT_TYPEID::ZERG_LARVA; 
        case sc2::UNIT_TYPEID::ZERG_MUTALISK:               return sc2::UNIT_TYPEID::ZERG_LARVA; 
        case sc2::UNIT_TYPEID::ZERG_QUEEN:                  return sc2::UNIT_TYPEID::ZERG_LARVA; 
        case sc2::UNIT_TYPEID::ZERG_ROACH:                  return sc2::UNIT_TYPEID::ZERG_LARVA; 
        case sc2::UNIT_TYPEID::ZERG_SWARMHOSTMP:            return sc2::UNIT_TYPEID::ZERG_LARVA;
        case sc2::UNIT_TYPEID::ZERG_ULTRALISK:              return sc2::UNIT_TYPEID::ZERG_LARVA; 
        case sc2::UNIT_TYPEID::ZERG_VIPER:                  return sc2::UNIT_TYPEID::ZERG_LARVA; 
        case sc2::UNIT_TYPEID::ZERG_ZERGLING:               return sc2::UNIT_TYPEID::ZERG_LARVA;
        case sc2::UNIT_TYPEID::ZERG_LAIR:                   return sc2::UNIT_TYPEID::ZERG_HATCHERY;
        case sc2::UNIT_TYPEID::ZERG_HIVE:                   return sc2::UNIT_TYPEID::ZERG_LAIR;  
        case sc2::UNIT_TYPEID::ZERG_GREATERSPIRE:           return sc2::UNIT_TYPEID::ZERG_SPIRE; 
       
        default: return 0;
    }
}

sc2::UnitTypeID Util::GetUnitTypeIDFromName(const sc2::ObservationInterface * obs, const std::string & name)
{
    for (const sc2::UnitTypeData & data : obs->GetUnitTypeData())
    {
        if (name == data.name)
        {
            return data.unit_type_id;
        }
    }

    std::cerr << "Unit Type Not Found: " << name << "\n";
    return 0;
}

UnitTag GetClosestEnemyUnitTo(const sc2::Unit & ourUnit, const sc2::ObservationInterface * obs)
{
    UnitTag closestTag = 0;
	double closestDist = std::numeric_limits<double>::max();

	for (auto & unit : obs->GetUnits())
	{
		double dist = Util::DistSq(unit.pos, ourUnit.pos);

		if (!closestTag || (dist < closestDist))
		{
			closestTag = unit;
			closestDist = dist;
		}
	}

	return closestTag;
}

bool Util::IsResearchAbility(const sc2::ABILITY_ID & ability) 
{
    switch (ability) 
    {
        /*case sc2::ABILITY_ID::RESEARCH_ADEPTRESEARCHPIERCINGUPGRADE: return true;
        case sc2::ABILITY_ID::RESEARCH_BANSHEESPEED: return true;
        case sc2::ABILITY_ID::RESEARCH_EVOLVECENTRIFICALHOOKS: return true;
        case sc2::ABILITY_ID::RESEARCH_EVOLVECHITINOUSPLATING: return true;
        case sc2::ABILITY_ID::RESEARCH_EVOLVEGLIALREGENERATION: return true;
        case sc2::ABILITY_ID::RESEARCH_EVOLVEGROOVEDSPINES: return true;
        case sc2::ABILITY_ID::RESEARCH_EVOLVEINFESTORENERGYUPGRADE: return true;
        case sc2::ABILITY_ID::RESEARCH_EVOLVEMUSCULARAUGMENTS: return true;
        case sc2::ABILITY_ID::RESEARCH_EVOLVETUNNELINGCLAWS: return true;
        case sc2::ABILITY_ID::RESEARCH_OVERLORDSPEED: return true;
        case sc2::ABILITY_ID::RESEARCH_PHOENIXRANGEUPGRADE: return true;*/
        case sc2::ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL1: return true;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL2: return true;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL3: return true;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL1: return true;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL2: return true;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL3: return true;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL1: return true;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL2: return true;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL3: return true;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL1: return true;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL2: return true;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL3: return true;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL1: return true;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL2: return true;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL3: return true;
        /*case sc2::ABILITY_ID::RESEARCH_RESEARCHBANSHEECLOAK: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHBATTLECRUISERSPECIALIZATIONS: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHBURROW: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHCHARGE: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHDARKTEMPLARBLINK: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHDRILLCLAWS: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHEXTENDEDTHERMALLANCE: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHGRAVITICBOOSTER: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHGRAVITICDRIVE: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHHIGHCAPACITYBARRELS: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHHISECAUTOTRACKING: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHMAGFIELDLAUNCHERS: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHNEOSTEELFRAME: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHNEURALPARASITE: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHPERSONALCLOAKING: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHPSISTORM: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHPUNISHERGRENADES: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHRAVENRECALIBRATEDEXPLOSIVES: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHSHIELDWALL: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHSTALKERTELEPORT: return true;
        case sc2::ABILITY_ID::RESEARCH_RESEARCHWARPGATE: return true;*/
        case sc2::ABILITY_ID::RESEARCH_STIMPACK: return true;
        case sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL1: return true;
        case sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL2: return true;
        case sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL3: return true;
        case sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL1: return true;
        case sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL2: return true;
        case sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL3: return true;
        case sc2::ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL1: return true;
        case sc2::ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL2: return true;
        case sc2::ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL3: return true;
        case sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL1: return true;
        case sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL2: return true;
        case sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL3: return true;
        case sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL1: return true;
        case sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL2: return true;
        case sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL3: return true;
        /*case sc2::ABILITY_ID::RESEARCH_UPGRADEBUILDINGARMORLEVEL1: return true;
        case sc2::ABILITY_ID::RESEARCH_ZERGFLYERARMOR1: return true;
        case sc2::ABILITY_ID::RESEARCH_ZERGFLYERARMOR2: return true;
        case sc2::ABILITY_ID::RESEARCH_ZERGFLYERARMOR3: return true;
        case sc2::ABILITY_ID::RESEARCH_ZERGFLYERATTACK1: return true;
        case sc2::ABILITY_ID::RESEARCH_ZERGFLYERATTACK2: return true;
        case sc2::ABILITY_ID::RESEARCH_ZERGFLYERATTACK3: return true;
        case sc2::ABILITY_ID::RESEARCH_ZERGGROUNDARMOR1: return true;
        case sc2::ABILITY_ID::RESEARCH_ZERGGROUNDARMOR2: return true;
        case sc2::ABILITY_ID::RESEARCH_ZERGGROUNDARMOR3: return true;
        case sc2::ABILITY_ID::RESEARCH_ZERGLINGATTACKSPEED: return true;
        case sc2::ABILITY_ID::RESEARCH_ZERGLINGMOVEMENTSPEED: return true;
        case sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONS1: return true;
        case sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONS2: return true;
        case sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONS3: return true;
        case sc2::ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONS1: return true;
        case sc2::ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONS2: return true;
        case sc2::ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONS3: return true;*/
        default: return false;
    }
}

bool Util::IsBuildCommand(const sc2::ABILITY_ID & ability) 
{
    switch (ability) 
    {
        case sc2::ABILITY_ID::BUILD_ARMORY: return true;
        case sc2::ABILITY_ID::BUILD_ASSIMILATOR: return true;
        case sc2::ABILITY_ID::BUILD_BANELINGNEST: return true;
        case sc2::ABILITY_ID::BUILD_BARRACKS: return true;
        case sc2::ABILITY_ID::BUILD_REACTOR_BARRACKS: return true;
        case sc2::ABILITY_ID::BUILD_TECHLAB_BARRACKS: return true;
        case sc2::ABILITY_ID::BUILD_BUNKER: return true;
        case sc2::ABILITY_ID::BUILD_COMMANDCENTER: return true;
        case sc2::ABILITY_ID::BUILD_CYBERNETICSCORE: return true;
        case sc2::ABILITY_ID::BUILD_DARKSHRINE: return true;
        case sc2::ABILITY_ID::BUILD_ENGINEERINGBAY: return true;
        case sc2::ABILITY_ID::BUILD_EVOLUTIONCHAMBER: return true;
        case sc2::ABILITY_ID::BUILD_EXTRACTOR: return true;
        case sc2::ABILITY_ID::BUILD_FACTORY: return true;
        case sc2::ABILITY_ID::BUILD_REACTOR_FACTORY: return true;
        case sc2::ABILITY_ID::BUILD_TECHLAB_FACTORY: return true;
        case sc2::ABILITY_ID::BUILD_FLEETBEACON: return true;
        case sc2::ABILITY_ID::BUILD_FORGE: return true;
        case sc2::ABILITY_ID::BUILD_FUSIONCORE: return true;
        case sc2::ABILITY_ID::BUILD_GATEWAY: return true;
        case sc2::ABILITY_ID::BUILD_GHOSTACADEMY: return true;
        case sc2::ABILITY_ID::BUILD_HATCHERY: return true;
        case sc2::ABILITY_ID::BUILD_HYDRALISKDEN: return true;
        case sc2::ABILITY_ID::BUILD_INFESTATIONPIT: return true;
        case sc2::ABILITY_ID::BUILD_INTERCEPTORS: return true;
        case sc2::ABILITY_ID::BUILD_MISSILETURRET: return true;
        case sc2::ABILITY_ID::BUILD_NEXUS: return true;
        case sc2::ABILITY_ID::BUILD_NUKE: return true;
        case sc2::ABILITY_ID::BUILD_NYDUSWORM: return true;
        case sc2::ABILITY_ID::BUILD_NYDUSNETWORK: return true;
        case sc2::ABILITY_ID::BUILD_STASISTRAP: return true;
        case sc2::ABILITY_ID::BUILD_PHOTONCANNON: return true;
        case sc2::ABILITY_ID::BUILD_PYLON: return true;
        case sc2::ABILITY_ID::BUILD_REFINERY: return true;
        case sc2::ABILITY_ID::BUILD_ROACHWARREN: return true;
        case sc2::ABILITY_ID::BUILD_ROBOTICSBAY: return true;
        case sc2::ABILITY_ID::BUILD_ROBOTICSFACILITY: return true;
        case sc2::ABILITY_ID::BUILD_SENSORTOWER: return true;
        case sc2::ABILITY_ID::BUILD_SPAWNINGPOOL: return true;
        case sc2::ABILITY_ID::BUILD_SPINECRAWLER: return true;
        case sc2::ABILITY_ID::BUILD_SPIRE: return true;
        case sc2::ABILITY_ID::BUILD_SPORECRAWLER: return true;
        case sc2::ABILITY_ID::BUILD_STARGATE: return true;
        case sc2::ABILITY_ID::BUILD_STARPORT: return true;
        case sc2::ABILITY_ID::BUILD_REACTOR_STARPORT: return true;
        case sc2::ABILITY_ID::BUILD_TECHLAB_STARPORT: return true;
        case sc2::ABILITY_ID::BUILD_SUPPLYDEPOT: return true;
        case sc2::ABILITY_ID::BUILD_TEMPLARARCHIVE: return true;
        case sc2::ABILITY_ID::BUILD_TWILIGHTCOUNCIL: return true;
        case sc2::ABILITY_ID::BUILD_ULTRALISKCAVERN: return true;
        case sc2::ABILITY_ID::MORPH_HIVE: return true;
        case sc2::ABILITY_ID::MORPH_LAIR: return true;
        case sc2::ABILITY_ID::MORPH_GREATERSPIRE: return true;
        case sc2::ABILITY_ID::MORPH_ORBITALCOMMAND: return true;
        case sc2::ABILITY_ID::MORPH_PLANETARYFORTRESS: return true;
        case sc2::ABILITY_ID::TRAINWARP_DARKTEMPLAR: return true;
        case sc2::ABILITY_ID::TRAINWARP_HIGHTEMPLAR: return true;
        case sc2::ABILITY_ID::TRAINWARP_SENTRY: return true;
        case sc2::ABILITY_ID::TRAINWARP_STALKER: return true;
        case sc2::ABILITY_ID::TRAINWARP_ADEPT: return true;
        case sc2::ABILITY_ID::TRAINWARP_ZEALOT: return true;
        case sc2::ABILITY_ID::TRAIN_BANELING: return true;
        case sc2::ABILITY_ID::TRAIN_BANSHEE: return true;
        case sc2::ABILITY_ID::TRAIN_BATTLECRUISER: return true;
        case sc2::ABILITY_ID::TRAIN_CYCLONE: return true;
        case sc2::ABILITY_ID::TRAIN_CARRIER: return true;
        case sc2::ABILITY_ID::TRAIN_COLOSSUS: return true;
        case sc2::ABILITY_ID::TRAIN_CORRUPTOR: return true;
        case sc2::ABILITY_ID::TRAIN_DARKTEMPLAR: return true;
        case sc2::ABILITY_ID::TRAIN_DRONE: return true;
        case sc2::ABILITY_ID::TRAIN_GHOST: return true;
        case sc2::ABILITY_ID::TRAIN_HELLION: return true;
        case sc2::ABILITY_ID::TRAIN_HIGHTEMPLAR: return true;
        case sc2::ABILITY_ID::TRAIN_HYDRALISK: return true;
        case sc2::ABILITY_ID::TRAIN_IMMORTAL: return true;
        case sc2::ABILITY_ID::TRAIN_INFESTOR: return true;
        case sc2::ABILITY_ID::TRAIN_LIBERATOR: return true;
        case sc2::ABILITY_ID::TRAIN_MARAUDER: return true;
        case sc2::ABILITY_ID::TRAIN_MARINE: return true;
        case sc2::ABILITY_ID::TRAIN_MEDIVAC: return true;
        case sc2::ABILITY_ID::TRAIN_MOTHERSHIPCORE: return true;
        case sc2::ABILITY_ID::TRAIN_MUTALISK: return true;
        case sc2::ABILITY_ID::TRAIN_OBSERVER: return true;
        case sc2::ABILITY_ID::TRAIN_ORACLE: return true;
        case sc2::ABILITY_ID::TRAIN_PHOENIX: return true;
        case sc2::ABILITY_ID::TRAIN_PROBE: return true;
        case sc2::ABILITY_ID::TRAIN_QUEEN: return true;
        case sc2::ABILITY_ID::TRAIN_RAVEN: return true;
        case sc2::ABILITY_ID::TRAIN_REAPER: return true;
        case sc2::ABILITY_ID::TRAIN_ROACH: return true;
        case sc2::ABILITY_ID::TRAIN_SCV: return true;
        case sc2::ABILITY_ID::TRAIN_SENTRY: return true;
        case sc2::ABILITY_ID::TRAIN_SIEGETANK: return true;
        case sc2::ABILITY_ID::TRAIN_STALKER: return true;
        case sc2::ABILITY_ID::TRAIN_SWARMHOST: return true;
        case sc2::ABILITY_ID::TRAIN_TEMPEST: return true;
        case sc2::ABILITY_ID::TRAIN_THOR: return true;
        case sc2::ABILITY_ID::TRAIN_ULTRALISK: return true;
        case sc2::ABILITY_ID::TRAIN_VIKINGFIGHTER: return true;
        case sc2::ABILITY_ID::TRAIN_VIPER: return true;
        case sc2::ABILITY_ID::TRAIN_VOIDRAY: return true;
        case sc2::ABILITY_ID::TRAIN_ADEPT: return true;
        case sc2::ABILITY_ID::TRAIN_DISRUPTOR: return true;
        case sc2::ABILITY_ID::TRAIN_WARPPRISM: return true;
        case sc2::ABILITY_ID::TRAIN_WIDOWMINE: return true;
        case sc2::ABILITY_ID::TRAIN_ZEALOT: return true;
        case sc2::ABILITY_ID::TRAIN_ZERGLING: return true;

        // Like a building.
        case sc2::ABILITY_ID::TRAIN_OVERLORD: return true;
        default: return false;
        // TODO - Add upgrades to switch statements.
    }

    // Not relevant.
    //case sc2::ABILITY_ID::BUILD_CREEPTUMOR: return true;
    //case sc2::ABILITY_ID::BUILD_QUEEN_CREEPTUMOR: return true;
}

sc2::UnitTypeID Util::AbilityIDToUnitTypeID(const sc2::AbilityID & ability) 
{
    switch (ability.ToType()) 
    {
        case sc2::ABILITY_ID::BUILD_ARMORY: return sc2::UNIT_TYPEID::TERRAN_ARMORY;
        case sc2::ABILITY_ID::BUILD_ASSIMILATOR: return sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR;
        case sc2::ABILITY_ID::BUILD_BANELINGNEST: return sc2::UNIT_TYPEID::ZERG_BANELINGNEST;
        case sc2::ABILITY_ID::BUILD_BARRACKS: return sc2::UNIT_TYPEID::TERRAN_BARRACKS;
        case sc2::ABILITY_ID::BUILD_REACTOR_BARRACKS: return sc2::UNIT_TYPEID::TERRAN_BARRACKSREACTOR;
        case sc2::ABILITY_ID::BUILD_TECHLAB_BARRACKS: return sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB;
        case sc2::ABILITY_ID::BUILD_BUNKER: return sc2::UNIT_TYPEID::TERRAN_BUNKER;
        case sc2::ABILITY_ID::BUILD_COMMANDCENTER: return sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER;
        //case sc2::ABILITY_ID::BUILD_CREEPTUMOR: return sc2::UNIT_TYPEID::ZERG_CREEPTUMOR;
        case sc2::ABILITY_ID::BUILD_CYBERNETICSCORE: return sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE;
        case sc2::ABILITY_ID::BUILD_DARKSHRINE: return sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE;
        case sc2::ABILITY_ID::BUILD_ENGINEERINGBAY: return sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY;
        case sc2::ABILITY_ID::BUILD_EVOLUTIONCHAMBER: return sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER;
        case sc2::ABILITY_ID::BUILD_EXTRACTOR: return sc2::UNIT_TYPEID::ZERG_EXTRACTOR;
        case sc2::ABILITY_ID::BUILD_FACTORY: return sc2::UNIT_TYPEID::TERRAN_FACTORY;
        case sc2::ABILITY_ID::BUILD_REACTOR_FACTORY: return sc2::UNIT_TYPEID::TERRAN_FACTORYREACTOR;
        case sc2::ABILITY_ID::BUILD_TECHLAB_FACTORY: return sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB;
        case sc2::ABILITY_ID::BUILD_FLEETBEACON: return sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON;
        case sc2::ABILITY_ID::BUILD_FORGE: return sc2::UNIT_TYPEID::PROTOSS_FORGE;
        case sc2::ABILITY_ID::BUILD_FUSIONCORE: return sc2::UNIT_TYPEID::TERRAN_FUSIONCORE;
        case sc2::ABILITY_ID::BUILD_GATEWAY: return sc2::UNIT_TYPEID::PROTOSS_GATEWAY;
        case sc2::ABILITY_ID::BUILD_GHOSTACADEMY: return sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY;
        case sc2::ABILITY_ID::BUILD_HATCHERY: return sc2::UNIT_TYPEID::ZERG_HATCHERY;
        case sc2::ABILITY_ID::BUILD_HYDRALISKDEN: return sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN;
        case sc2::ABILITY_ID::BUILD_INFESTATIONPIT: return sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT;
        case sc2::ABILITY_ID::BUILD_INTERCEPTORS: return sc2::UNIT_TYPEID::PROTOSS_INTERCEPTOR;
        case sc2::ABILITY_ID::BUILD_MISSILETURRET: return sc2::UNIT_TYPEID::TERRAN_MISSILETURRET;
        case sc2::ABILITY_ID::BUILD_NEXUS: return sc2::UNIT_TYPEID::PROTOSS_NEXUS;
        case sc2::ABILITY_ID::BUILD_NUKE: return sc2::UNIT_TYPEID::TERRAN_NUKE;
        case sc2::ABILITY_ID::BUILD_NYDUSWORM: return sc2::UNIT_TYPEID::ZERG_NYDUSCANAL;
        case sc2::ABILITY_ID::BUILD_NYDUSNETWORK: return sc2::UNIT_TYPEID::ZERG_NYDUSNETWORK;
        case sc2::ABILITY_ID::BUILD_STASISTRAP: return sc2::UNIT_TYPEID::PROTOSS_ORACLESTASISTRAP;
        case sc2::ABILITY_ID::BUILD_PHOTONCANNON: return sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON;
        case sc2::ABILITY_ID::BUILD_PYLON: return sc2::UNIT_TYPEID::PROTOSS_PYLON;
        case sc2::ABILITY_ID::BUILD_CREEPTUMOR_QUEEN: return sc2::UNIT_TYPEID::ZERG_CREEPTUMORQUEEN;
        case sc2::ABILITY_ID::BUILD_REFINERY: return sc2::UNIT_TYPEID::TERRAN_REFINERY;
        case sc2::ABILITY_ID::BUILD_ROACHWARREN: return sc2::UNIT_TYPEID::ZERG_ROACHWARREN;
        case sc2::ABILITY_ID::BUILD_ROBOTICSBAY: return sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY;
        case sc2::ABILITY_ID::BUILD_ROBOTICSFACILITY: return sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY;
        case sc2::ABILITY_ID::BUILD_SENSORTOWER: return sc2::UNIT_TYPEID::TERRAN_SENSORTOWER;
        case sc2::ABILITY_ID::BUILD_SPAWNINGPOOL: return sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL;
        case sc2::ABILITY_ID::BUILD_SPINECRAWLER: return sc2::UNIT_TYPEID::ZERG_SPINECRAWLER;
        case sc2::ABILITY_ID::BUILD_SPIRE: return sc2::UNIT_TYPEID::ZERG_SPIRE;
        case sc2::ABILITY_ID::BUILD_SPORECRAWLER: return sc2::UNIT_TYPEID::ZERG_SPORECRAWLER;
        case sc2::ABILITY_ID::BUILD_STARGATE: return sc2::UNIT_TYPEID::PROTOSS_STARGATE;
        case sc2::ABILITY_ID::BUILD_STARPORT: return sc2::UNIT_TYPEID::TERRAN_STARPORT;
        case sc2::ABILITY_ID::BUILD_REACTOR_STARPORT: return sc2::UNIT_TYPEID::TERRAN_STARPORTREACTOR;
        case sc2::ABILITY_ID::BUILD_TECHLAB_STARPORT: return sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB;
        case sc2::ABILITY_ID::BUILD_SUPPLYDEPOT: return sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT;
        case sc2::ABILITY_ID::BUILD_TEMPLARARCHIVE: return sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE;
        case sc2::ABILITY_ID::BUILD_TWILIGHTCOUNCIL: return sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL;
        case sc2::ABILITY_ID::BUILD_ULTRALISKCAVERN: return sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN;
        case sc2::ABILITY_ID::MORPH_HIVE: return sc2::UNIT_TYPEID::ZERG_HIVE;
        case sc2::ABILITY_ID::MORPH_LAIR: return sc2::UNIT_TYPEID::ZERG_LAIR;
        case sc2::ABILITY_ID::MORPH_GREATERSPIRE: return sc2::UNIT_TYPEID::ZERG_GREATERSPIRE;
        case sc2::ABILITY_ID::MORPH_ORBITALCOMMAND: return sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND;
        case sc2::ABILITY_ID::MORPH_PLANETARYFORTRESS: return sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS;
        case sc2::ABILITY_ID::TRAIN_OVERLORD: return sc2::UNIT_TYPEID::ZERG_OVERLORD;
        case sc2::ABILITY_ID::TRAINWARP_DARKTEMPLAR: return sc2::UNIT_TYPEID::PROTOSS_DARKTEMPLAR;
        case sc2::ABILITY_ID::TRAINWARP_HIGHTEMPLAR: return sc2::UNIT_TYPEID::PROTOSS_HIGHTEMPLAR;
        case sc2::ABILITY_ID::TRAINWARP_SENTRY: return sc2::UNIT_TYPEID::PROTOSS_SENTRY;
        case sc2::ABILITY_ID::TRAINWARP_STALKER: return sc2::UNIT_TYPEID::PROTOSS_STALKER;
        case sc2::ABILITY_ID::TRAINWARP_ADEPT: return sc2::UNIT_TYPEID::PROTOSS_ADEPT;
        case sc2::ABILITY_ID::TRAINWARP_ZEALOT: return sc2::UNIT_TYPEID::PROTOSS_ZEALOT;
        case sc2::ABILITY_ID::TRAIN_BANELING: return sc2::UNIT_TYPEID::ZERG_BANELING;
        case sc2::ABILITY_ID::TRAIN_BANSHEE: return sc2::UNIT_TYPEID::TERRAN_BANSHEE;
        case sc2::ABILITY_ID::TRAIN_BATTLECRUISER: return sc2::UNIT_TYPEID::TERRAN_BATTLECRUISER;
        case sc2::ABILITY_ID::TRAIN_CYCLONE: return sc2::UNIT_TYPEID::TERRAN_CYCLONE;
        case sc2::ABILITY_ID::TRAIN_CARRIER: return sc2::UNIT_TYPEID::PROTOSS_CARRIER;
        case sc2::ABILITY_ID::TRAIN_COLOSSUS: return sc2::UNIT_TYPEID::PROTOSS_COLOSSUS;
        case sc2::ABILITY_ID::TRAIN_CORRUPTOR: return sc2::UNIT_TYPEID::ZERG_CORRUPTOR;
        case sc2::ABILITY_ID::TRAIN_DARKTEMPLAR: return sc2::UNIT_TYPEID::PROTOSS_DARKTEMPLAR;
        case sc2::ABILITY_ID::TRAIN_DRONE: return sc2::UNIT_TYPEID::ZERG_DRONE;
        case sc2::ABILITY_ID::TRAIN_GHOST: return sc2::UNIT_TYPEID::TERRAN_GHOST;
        case sc2::ABILITY_ID::TRAIN_HELLION: return sc2::UNIT_TYPEID::TERRAN_HELLION;
        case sc2::ABILITY_ID::TRAIN_HIGHTEMPLAR: return sc2::UNIT_TYPEID::PROTOSS_HIGHTEMPLAR;
        case sc2::ABILITY_ID::TRAIN_HYDRALISK: return sc2::UNIT_TYPEID::ZERG_HYDRALISK;
        case sc2::ABILITY_ID::TRAIN_IMMORTAL: return sc2::UNIT_TYPEID::PROTOSS_IMMORTAL;
        case sc2::ABILITY_ID::TRAIN_INFESTOR: return sc2::UNIT_TYPEID::ZERG_INFESTOR;
        case sc2::ABILITY_ID::TRAIN_LIBERATOR: return sc2::UNIT_TYPEID::TERRAN_LIBERATOR;
        case sc2::ABILITY_ID::TRAIN_MARAUDER: return sc2::UNIT_TYPEID::TERRAN_MARAUDER;
        case sc2::ABILITY_ID::TRAIN_MARINE: return sc2::UNIT_TYPEID::TERRAN_MARINE;
        case sc2::ABILITY_ID::TRAIN_MEDIVAC: return sc2::UNIT_TYPEID::TERRAN_MEDIVAC;
        case sc2::ABILITY_ID::TRAIN_MOTHERSHIPCORE: return sc2::UNIT_TYPEID::PROTOSS_MOTHERSHIPCORE;
        case sc2::ABILITY_ID::TRAIN_MUTALISK: return sc2::UNIT_TYPEID::ZERG_MUTALISK;
        case sc2::ABILITY_ID::TRAIN_OBSERVER: return sc2::UNIT_TYPEID::PROTOSS_OBSERVER;
        case sc2::ABILITY_ID::TRAIN_ORACLE: return sc2::UNIT_TYPEID::PROTOSS_ORACLE;
        case sc2::ABILITY_ID::TRAIN_PHOENIX: return sc2::UNIT_TYPEID::PROTOSS_PHOENIX;
        case sc2::ABILITY_ID::TRAIN_PROBE: return sc2::UNIT_TYPEID::PROTOSS_PROBE;
        case sc2::ABILITY_ID::TRAIN_QUEEN: return sc2::UNIT_TYPEID::ZERG_QUEEN;
        case sc2::ABILITY_ID::TRAIN_RAVEN: return sc2::UNIT_TYPEID::TERRAN_RAVEN;
        //case sc2::ABILITY_ID::TRAIN_REAPER: return sc2::UNIT_TYPEID::REA;
        case sc2::ABILITY_ID::TRAIN_ROACH: return sc2::UNIT_TYPEID::ZERG_ROACH;
        case sc2::ABILITY_ID::TRAIN_SCV: return sc2::UNIT_TYPEID::TERRAN_SCV;
        case sc2::ABILITY_ID::TRAIN_SENTRY: return sc2::UNIT_TYPEID::PROTOSS_SENTRY;
        case sc2::ABILITY_ID::TRAIN_SIEGETANK: return sc2::UNIT_TYPEID::TERRAN_SIEGETANK;
        case sc2::ABILITY_ID::TRAIN_STALKER: return sc2::UNIT_TYPEID::PROTOSS_STALKER;
        case sc2::ABILITY_ID::TRAIN_SWARMHOST: return sc2::UNIT_TYPEID::ZERG_SWARMHOSTMP;
        case sc2::ABILITY_ID::TRAIN_TEMPEST: return sc2::UNIT_TYPEID::PROTOSS_TEMPEST;
        case sc2::ABILITY_ID::TRAIN_THOR: return sc2::UNIT_TYPEID::TERRAN_THOR;
        case sc2::ABILITY_ID::TRAIN_ULTRALISK: return sc2::UNIT_TYPEID::ZERG_ULTRALISK;
        case sc2::ABILITY_ID::TRAIN_VIKINGFIGHTER: return sc2::UNIT_TYPEID::TERRAN_VIKINGFIGHTER;
        case sc2::ABILITY_ID::TRAIN_VIPER: return sc2::UNIT_TYPEID::ZERG_VIPER;
        case sc2::ABILITY_ID::TRAIN_VOIDRAY: return sc2::UNIT_TYPEID::PROTOSS_VOIDRAY;
        case sc2::ABILITY_ID::TRAIN_ADEPT: return sc2::UNIT_TYPEID::PROTOSS_ADEPT;
        case sc2::ABILITY_ID::TRAIN_DISRUPTOR: return sc2::UNIT_TYPEID::PROTOSS_DISRUPTOR;
        case sc2::ABILITY_ID::TRAIN_WARPPRISM: return sc2::UNIT_TYPEID::PROTOSS_WARPPRISM;
        case sc2::ABILITY_ID::TRAIN_WIDOWMINE: return sc2::UNIT_TYPEID::TERRAN_WIDOWMINE;
        case sc2::ABILITY_ID::TRAIN_ZEALOT: return sc2::UNIT_TYPEID::PROTOSS_ZEALOT;
        case sc2::ABILITY_ID::TRAIN_ZERGLING: return sc2::UNIT_TYPEID::ZERG_ZERGLING;

        default: return 0;
    }
}

// TODO - Find missing ability/upgrade pairings.
sc2::UpgradeID Util::AbilityIDToUpgradeID(const sc2::AbilityID & ability) 
{
    switch (ability.ToType()) 
    {
        //case sc2::ABILITY_ID::RESEARCH_ADEPTRESEARCHPIERCINGUPGRADE:            return sc2::UPGRADE_ID::ADEPTPIERCINGATTACK;
        //case sc2::ABILITY_ID::RESEARCH_BANSHEESPEED:                            return sc2::UPGRADE_ID::BANSHEESPEED;
        //case sc2::ABILITY_ID::RESEARCH_EVOLVECENTRIFICALHOOKS:                  return sc2::UPGRADE_ID::CENTRIFICALHOOKS;
        //case sc2::ABILITY_ID::RESEARCH_EVOLVECHITINOUSPLATING:                  return sc2::UPGRADE_ID::CHITINOUSPLATING;
        //case sc2::ABILITY_ID::RESEARCH_EVOLVEGLIALREGENERATION:                 return sc2::UPGRADE_ID::GLIALRECONSTITUTION;
        //case sc2::ABILITY_ID::RESEARCH_EVOLVEGROOVEDSPINES:                     return sc2::UPGRADE_ID::EVOLVEGROOVEDSPINES;
        //case sc2::ABILITY_ID::RESEARCH_EVOLVEINFESTORENERGYUPGRADE:             return sc2::UPGRADE_ID::INFESTORENERGYUPGRADE;
        //case sc2::ABILITY_ID::RESEARCH_EVOLVEMUSCULARAUGMENTS:                  return sc2::UPGRADE_ID::EVOLVEMUSCULARAUGMENTS;
        //case sc2::ABILITY_ID::RESEARCH_EVOLVETUNNELINGCLAWS:                    return sc2::UPGRADE_ID::TUNNELINGCLAWS;
        //case sc2::ABILITY_ID::RESEARCH_OVERLORDSPEED:                           return sc2::UPGRADE_ID::OVERLORDSPEED;
        //case sc2::ABILITY_ID::RESEARCH_PHOENIXRANGEUPGRADE:                     return sc2::UPGRADE_ID::PHOENIXRANGEUPGRADE;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL1:                   return sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL1;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL2:                   return sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL2;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL3:                   return sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL3;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL1:                 return sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL1;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL2:                 return sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL2;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL3:                 return sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL3;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL1:                return sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL1;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL2:                return sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL2;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL3:                return sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL3;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL1:              return sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL1;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL2:              return sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL2;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL3:              return sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL3;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL1:                    return sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL1;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL2:                    return sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL2;
        case sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL3:                    return sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL3;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHBANSHEECLOAK:                    return sc2::UPGRADE_ID::BANSHEECLOAK;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHBATTLECRUISERSPECIALIZATIONS:    return sc2::UPGRADE_ID::BATTLECRUISERENABLESPECIALIZATIONS;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHBURROW:                          return sc2::UPGRADE_ID::BURROW;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHCHARGE:                          return sc2::UPGRADE_ID::CHARGE;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHDARKTEMPLARBLINK:                return sc2::UPGRADE_ID::DARKTEMPLARBLINKUPGRADE;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHDRILLCLAWS:                      return sc2::UPGRADE_ID::DRILLCLAWS;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHEXTENDEDTHERMALLANCE:            return sc2::UPGRADE_ID::EXTENDEDTHERMALLANCE;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHGRAVITICBOOSTER:                 return sc2::UPGRADE_ID::OBSERVERGRAVITICBOOSTER;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHGRAVITICDRIVE:                   return sc2::UPGRADE_ID::GRAVITICDRIVE;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHHIGHCAPACITYBARRELS:             return sc2::UPGRADE_ID::HIGHCAPACITYBARRELS;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHHISECAUTOTRACKING:               return sc2::UPGRADE_ID::HISECAUTOTRACKING;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHMAGFIELDLAUNCHERS:               return sc2::UPGRADE_ID::MAGFIELDLAUNCHERS;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHNEOSTEELFRAME:                   return sc2::UPGRADE_ID::NEOSTEELFRAME;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHNEURALPARASITE:                  return sc2::UPGRADE_ID::NEURALPARASITE;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHPERSONALCLOAKING:                return sc2::UPGRADE_ID::PERSONALCLOAKING;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHPSISTORM:                        return sc2::UPGRADE_ID::PSISTORMTECH;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHPUNISHERGRENADES:                return sc2::UPGRADE_ID::PUNISHERGRENADES;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHRAVENRECALIBRATEDEXPLOSIVES:     return sc2::UPGRADE_ID::RAVENRECALIBRATEDEXPLOSIVES;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHSHIELDWALL:                      return sc2::UPGRADE_ID::SHIELDWALL;
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHSTALKERTELEPORT:                 return sc2::UPGRADE_ID::BLINKTECH; // 'Stalker teleport".
        //case sc2::ABILITY_ID::RESEARCH_RESEARCHWARPGATE:                        return sc2::UPGRADE_ID::WARPGATERESEARCH;
        case sc2::ABILITY_ID::RESEARCH_STIMPACK:                                return sc2::UPGRADE_ID::STIMPACK;
        case sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL1:               return sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL1;
        case sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL2:               return sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL2;
        case sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL3:               return sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL3;
        case sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL1:             return sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL1;
        case sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL2:             return sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL2;
        case sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL3:             return sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL3;
        case sc2::ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL1:                 return sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL1;
        case sc2::ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL2:                 return sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL2;
        case sc2::ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL3:                 return sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL3;
        case sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL1:       return sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL1;
        case sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL2:       return sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL2;
        case sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL3:       return sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL3;
        case sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL1:              return sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL1;
        case sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL2:              return sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL2;
        case sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL3:              return sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL3;
        /*case sc2::ABILITY_ID::RESEARCH_UPGRADEBUILDINGARMORLEVEL1:              return sc2::UPGRADE_ID::TERRANBUILDINGARMOR;
        case sc2::ABILITY_ID::RESEARCH_ZERGFLYERARMOR1:                         return sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL1;
        case sc2::ABILITY_ID::RESEARCH_ZERGFLYERARMOR2:                         return sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL2;
        case sc2::ABILITY_ID::RESEARCH_ZERGFLYERARMOR3:                         return sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL3;
        case sc2::ABILITY_ID::RESEARCH_ZERGFLYERATTACK1:                        return sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL1;
        case sc2::ABILITY_ID::RESEARCH_ZERGFLYERATTACK2:                        return sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL2;
        case sc2::ABILITY_ID::RESEARCH_ZERGFLYERATTACK3:                        return sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL3;
        case sc2::ABILITY_ID::RESEARCH_ZERGGROUNDARMOR1:                        return sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL1;
        case sc2::ABILITY_ID::RESEARCH_ZERGGROUNDARMOR2:                        return sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL2;
        case sc2::ABILITY_ID::RESEARCH_ZERGGROUNDARMOR3:                        return sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL3;
        case sc2::ABILITY_ID::RESEARCH_ZERGLINGATTACKSPEED:                     return sc2::UPGRADE_ID::ZERGLINGATTACKSPEED;
        case sc2::ABILITY_ID::RESEARCH_ZERGLINGMOVEMENTSPEED:                   return sc2::UPGRADE_ID::ZERGLINGMOVEMENTSPEED;
        case sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONS1:                       return sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL1;
        case sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONS2:                       return sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL2;
        case sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONS3:                       return sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL3;
        case sc2::ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONS1:                     return sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL1;
        case sc2::ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONS2:                     return sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL2;
        case sc2::ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONS3:                     return sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL3;*/
        default: return false;
    }
}

bool Util::IsMorphCommand(const sc2::AbilityID & ability) 
{
    switch (ability.ToType()) 
    {
        case sc2::ABILITY_ID::MORPH_HIVE:               return true;
        case sc2::ABILITY_ID::MORPH_LAIR:               return true;
        case sc2::ABILITY_ID::MORPH_GREATERSPIRE:       return true;
        case sc2::ABILITY_ID::MORPH_ORBITALCOMMAND:     return true;
        case sc2::ABILITY_ID::MORPH_PLANETARYFORTRESS:  return true;
        case sc2::ABILITY_ID::TRAIN_OVERLORD:           return true;
        default: return false;
    }
}

// TODO - Add all variations of units to list.
sc2::UnitTypeID Util::GetEquivalentUnitTypeID(const sc2::UnitTypeID & id) 
{
	switch (id.ToType()) 
    {
        case sc2::UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING:  return sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER;
	    case sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOTLOWERED:   return sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT;
	    case sc2::UNIT_TYPEID::TERRAN_BARRACKSFLYING:       return sc2::UNIT_TYPEID::TERRAN_BARRACKS;
	    case sc2::UNIT_TYPEID::TERRAN_FACTORYFLYING:        return sc2::UNIT_TYPEID::TERRAN_FACTORY;
	    case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING: return sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND;
	    case sc2::UNIT_TYPEID::TERRAN_STARPORTFLYING:       return sc2::UNIT_TYPEID::TERRAN_STARPORT;
        case sc2::UNIT_TYPEID::ZERG_SPINECRAWLERUPROOTED:   return sc2::UNIT_TYPEID::ZERG_SPINECRAWLER;
        case sc2::UNIT_TYPEID::ZERG_SPORECRAWLERUPROOTED:   return sc2::UNIT_TYPEID::ZERG_SPORECRAWLER;
        case sc2::UNIT_TYPEID::PROTOSS_WARPGATE:            return sc2::UNIT_TYPEID::PROTOSS_GATEWAY;
	}
	return id;
}

sc2::AbilityID Util::UnitTypeIDToAbilityID(const sc2::UnitTypeID & id)
{
    switch (id.ToType()) 
    {
        case sc2::UNIT_TYPEID::TERRAN_ARMORY: return sc2::ABILITY_ID::BUILD_ARMORY; 
        case sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR: return sc2::ABILITY_ID::BUILD_ASSIMILATOR; 
        case sc2::UNIT_TYPEID::ZERG_BANELINGNEST: return sc2::ABILITY_ID::BUILD_BANELINGNEST; 
        case sc2::UNIT_TYPEID::TERRAN_BARRACKS: return sc2::ABILITY_ID::BUILD_BARRACKS; 
        case sc2::UNIT_TYPEID::TERRAN_BARRACKSREACTOR: return sc2::ABILITY_ID::BUILD_REACTOR_BARRACKS; 
        case sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB: return sc2::ABILITY_ID::BUILD_TECHLAB_FACTORY; 
        case sc2::UNIT_TYPEID::TERRAN_BUNKER: return sc2::ABILITY_ID::BUILD_BUNKER; 
        case sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER: return sc2::ABILITY_ID::BUILD_COMMANDCENTER; 
        case sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE: return sc2::ABILITY_ID::BUILD_CYBERNETICSCORE; 
        case sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE: return sc2::ABILITY_ID::BUILD_DARKSHRINE; 
        case sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY: return sc2::ABILITY_ID::BUILD_ENGINEERINGBAY; 
        case sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER: return sc2::ABILITY_ID::BUILD_EVOLUTIONCHAMBER; 
        case sc2::UNIT_TYPEID::ZERG_EXTRACTOR: return sc2::ABILITY_ID::BUILD_EXTRACTOR; 
        case sc2::UNIT_TYPEID::TERRAN_FACTORY: return sc2::ABILITY_ID::BUILD_FACTORY; 
        case sc2::UNIT_TYPEID::TERRAN_FACTORYREACTOR: return sc2::ABILITY_ID::BUILD_REACTOR_FACTORY; 
        case sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB: return sc2::ABILITY_ID::BUILD_TECHLAB_FACTORY; 
        case sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON: return sc2::ABILITY_ID::BUILD_FLEETBEACON; 
        case sc2::UNIT_TYPEID::PROTOSS_FORGE: return sc2::ABILITY_ID::BUILD_FORGE; 
        case sc2::UNIT_TYPEID::TERRAN_FUSIONCORE: return sc2::ABILITY_ID::BUILD_FUSIONCORE; 
        case sc2::UNIT_TYPEID::PROTOSS_GATEWAY: return sc2::ABILITY_ID::BUILD_GATEWAY; 
        case sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY: return sc2::ABILITY_ID::BUILD_GHOSTACADEMY; 
        case sc2::UNIT_TYPEID::ZERG_HATCHERY: return sc2::ABILITY_ID::BUILD_HATCHERY; 
        case sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN: return sc2::ABILITY_ID::BUILD_HYDRALISKDEN; 
        case sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT: return sc2::ABILITY_ID::BUILD_INFESTATIONPIT; 
        case sc2::UNIT_TYPEID::PROTOSS_INTERCEPTOR: return sc2::ABILITY_ID::BUILD_INTERCEPTORS; 
        case sc2::UNIT_TYPEID::TERRAN_MISSILETURRET: return sc2::ABILITY_ID::BUILD_MISSILETURRET; 
        case sc2::UNIT_TYPEID::PROTOSS_NEXUS: return sc2::ABILITY_ID::BUILD_NEXUS; 
        case sc2::UNIT_TYPEID::TERRAN_NUKE: return sc2::ABILITY_ID::BUILD_NUKE; 
        case sc2::UNIT_TYPEID::ZERG_NYDUSCANAL: return sc2::ABILITY_ID::BUILD_NYDUSWORM; 
        case sc2::UNIT_TYPEID::ZERG_NYDUSNETWORK: return sc2::ABILITY_ID::BUILD_NYDUSNETWORK; 
        case sc2::UNIT_TYPEID::PROTOSS_ORACLESTASISTRAP: return sc2::ABILITY_ID::BUILD_STASISTRAP; 
        case sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON: return sc2::ABILITY_ID::BUILD_PHOTONCANNON; 
        case sc2::UNIT_TYPEID::PROTOSS_PYLON: return sc2::ABILITY_ID::BUILD_PYLON; 
        //return sc2::ABILITY_ID::BUILD_QUEEN_CREEPTUMOR; case sc2::UNIT_TYPEID::ZERG_CREEPTUMORQUEEN: 
        case sc2::UNIT_TYPEID::TERRAN_REFINERY: return sc2::ABILITY_ID::BUILD_REFINERY; 
        case sc2::UNIT_TYPEID::ZERG_ROACHWARREN: return sc2::ABILITY_ID::BUILD_ROACHWARREN; 
        case sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY: return sc2::ABILITY_ID::BUILD_ROBOTICSBAY; 
        case sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY: return sc2::ABILITY_ID::BUILD_ROBOTICSFACILITY; 
        case sc2::UNIT_TYPEID::TERRAN_SENSORTOWER: return sc2::ABILITY_ID::BUILD_SENSORTOWER; 
        case sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL: return sc2::ABILITY_ID::BUILD_SPAWNINGPOOL; 
        case sc2::UNIT_TYPEID::ZERG_SPINECRAWLER: return sc2::ABILITY_ID::BUILD_SPINECRAWLER; 
        case sc2::UNIT_TYPEID::ZERG_SPIRE: return sc2::ABILITY_ID::BUILD_SPIRE; 
        case sc2::UNIT_TYPEID::ZERG_SPORECRAWLER: return sc2::ABILITY_ID::BUILD_SPORECRAWLER; 
        case sc2::UNIT_TYPEID::PROTOSS_STARGATE: return sc2::ABILITY_ID::BUILD_STARGATE; 
        case sc2::UNIT_TYPEID::TERRAN_STARPORT: return sc2::ABILITY_ID::BUILD_STARPORT; 
        case sc2::UNIT_TYPEID::TERRAN_STARPORTREACTOR: return sc2::ABILITY_ID::BUILD_REACTOR_STARPORT; 
        case sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB: return sc2::ABILITY_ID::BUILD_TECHLAB_STARPORT; 
        case sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT: return sc2::ABILITY_ID::BUILD_SUPPLYDEPOT; 
        case sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE: return sc2::ABILITY_ID::BUILD_TEMPLARARCHIVE; 
        case sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL: return sc2::ABILITY_ID::BUILD_TWILIGHTCOUNCIL; 
        case sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN: return sc2::ABILITY_ID::BUILD_ULTRALISKCAVERN; 
        case sc2::UNIT_TYPEID::ZERG_HIVE: return sc2::ABILITY_ID::MORPH_HIVE; 
        case sc2::UNIT_TYPEID::ZERG_LAIR: return sc2::ABILITY_ID::MORPH_LAIR; 
        case sc2::UNIT_TYPEID::ZERG_GREATERSPIRE: return sc2::ABILITY_ID::MORPH_GREATERSPIRE; 
        case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND: return sc2::ABILITY_ID::MORPH_ORBITALCOMMAND; 
        case sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS: return sc2::ABILITY_ID::MORPH_PLANETARYFORTRESS; 
        case sc2::UNIT_TYPEID::ZERG_OVERLORD: return sc2::ABILITY_ID::TRAIN_OVERLORD; 
        /*case sc2::UNIT_TYPEID::PROTOSS_DARKTEMPLAR: return sc2::ABILITY_ID::TRAINWARP_DARKTEMPLAR; 
        case sc2::UNIT_TYPEID::PROTOSS_HIGHTEMPLAR: return sc2::ABILITY_ID::TRAINWARP_HIGHTEMPLAR; 
        case sc2::UNIT_TYPEID::PROTOSS_SENTRY: return sc2::ABILITY_ID::TRAINWARP_SENTRY; 
        case sc2::UNIT_TYPEID::PROTOSS_STALKER: return sc2::ABILITY_ID::TRAINWARP_STALKER; 
        case sc2::UNIT_TYPEID::PROTOSS_ADEPT: return sc2::ABILITY_ID::TRAINWARP_WARPINADEPT; 
        case sc2::UNIT_TYPEID::PROTOSS_ZEALOT: return sc2::ABILITY_ID::TRAINWARP_ZEALOT; */
        case sc2::UNIT_TYPEID::ZERG_BANELING: return sc2::ABILITY_ID::TRAIN_BANELING; 
        case sc2::UNIT_TYPEID::TERRAN_BANSHEE: return sc2::ABILITY_ID::TRAIN_BANSHEE; 
        case sc2::UNIT_TYPEID::TERRAN_BATTLECRUISER: return sc2::ABILITY_ID::TRAIN_BATTLECRUISER; 
        case sc2::UNIT_TYPEID::TERRAN_CYCLONE: return sc2::ABILITY_ID::TRAIN_CYCLONE; 
        case sc2::UNIT_TYPEID::PROTOSS_CARRIER: return sc2::ABILITY_ID::TRAIN_CARRIER; 
        case sc2::UNIT_TYPEID::PROTOSS_COLOSSUS: return sc2::ABILITY_ID::TRAIN_COLOSSUS; 
        case sc2::UNIT_TYPEID::ZERG_CORRUPTOR: return sc2::ABILITY_ID::TRAIN_CORRUPTOR;
        case sc2::UNIT_TYPEID::PROTOSS_DARKTEMPLAR: return sc2::ABILITY_ID::TRAIN_DARKTEMPLAR; 
        case sc2::UNIT_TYPEID::ZERG_DRONE: return sc2::ABILITY_ID::TRAIN_DRONE; 
        case sc2::UNIT_TYPEID::TERRAN_GHOST: return sc2::ABILITY_ID::TRAIN_GHOST; 
        case sc2::UNIT_TYPEID::TERRAN_HELLION: return sc2::ABILITY_ID::TRAIN_HELLION; 
        //case sc2::UNIT_TYPEID::TERRAN_HELLION: return sc2::ABILITY_ID::TRAIN_HELLIONTANK; 
        case sc2::UNIT_TYPEID::PROTOSS_HIGHTEMPLAR: return sc2::ABILITY_ID::TRAIN_HIGHTEMPLAR; 
        case sc2::UNIT_TYPEID::ZERG_HYDRALISK: return sc2::ABILITY_ID::TRAIN_HYDRALISK; 
        case sc2::UNIT_TYPEID::PROTOSS_IMMORTAL: return sc2::ABILITY_ID::TRAIN_IMMORTAL;
        case sc2::UNIT_TYPEID::ZERG_INFESTOR: return sc2::ABILITY_ID::TRAIN_INFESTOR; 
        case sc2::UNIT_TYPEID::TERRAN_LIBERATOR: return sc2::ABILITY_ID::TRAIN_LIBERATOR; 
        case sc2::UNIT_TYPEID::TERRAN_MARAUDER: return sc2::ABILITY_ID::TRAIN_MARAUDER; 
        case sc2::UNIT_TYPEID::TERRAN_MARINE: return sc2::ABILITY_ID::TRAIN_MARINE; 
        case sc2::UNIT_TYPEID::TERRAN_MEDIVAC: return sc2::ABILITY_ID::TRAIN_MEDIVAC; 
        case sc2::UNIT_TYPEID::PROTOSS_MOTHERSHIPCORE: return sc2::ABILITY_ID::TRAIN_MOTHERSHIPCORE; 
        case sc2::UNIT_TYPEID::ZERG_MUTALISK: return sc2::ABILITY_ID::TRAIN_MUTALISK; 
        case sc2::UNIT_TYPEID::PROTOSS_OBSERVER: return sc2::ABILITY_ID::TRAIN_OBSERVER; 
        case sc2::UNIT_TYPEID::PROTOSS_ORACLE: return sc2::ABILITY_ID::TRAIN_ORACLE; 
        case sc2::UNIT_TYPEID::PROTOSS_PHOENIX: return sc2::ABILITY_ID::TRAIN_PHOENIX; 
        case sc2::UNIT_TYPEID::PROTOSS_PROBE: return sc2::ABILITY_ID::TRAIN_PROBE; 
        case sc2::UNIT_TYPEID::ZERG_QUEEN: return sc2::ABILITY_ID::TRAIN_QUEEN; 
        case sc2::UNIT_TYPEID::TERRAN_RAVEN: return sc2::ABILITY_ID::TRAIN_RAVEN; 
        //return sc2::ABILITY_ID::TRAIN_REAPER; case sc2::UNIT_TYPEID::REA: 
        case sc2::UNIT_TYPEID::ZERG_ROACH: return sc2::ABILITY_ID::TRAIN_ROACH; 
        case sc2::UNIT_TYPEID::TERRAN_SCV: return sc2::ABILITY_ID::TRAIN_SCV; 
        case sc2::UNIT_TYPEID::PROTOSS_SENTRY: return sc2::ABILITY_ID::TRAIN_SENTRY; 
        case sc2::UNIT_TYPEID::TERRAN_SIEGETANK: return sc2::ABILITY_ID::TRAIN_SIEGETANK; 
        case sc2::UNIT_TYPEID::PROTOSS_STALKER: return sc2::ABILITY_ID::TRAIN_STALKER; 
        case sc2::UNIT_TYPEID::ZERG_SWARMHOSTMP: return sc2::ABILITY_ID::TRAIN_SWARMHOST; 
        case sc2::UNIT_TYPEID::PROTOSS_TEMPEST: return sc2::ABILITY_ID::TRAIN_TEMPEST; 
        case sc2::UNIT_TYPEID::TERRAN_THOR: return sc2::ABILITY_ID::TRAIN_THOR; 
        case sc2::UNIT_TYPEID::ZERG_ULTRALISK: return sc2::ABILITY_ID::TRAIN_ULTRALISK; 
        case sc2::UNIT_TYPEID::TERRAN_VIKINGFIGHTER: return sc2::ABILITY_ID::TRAIN_VIKINGFIGHTER; 
        case sc2::UNIT_TYPEID::ZERG_VIPER: return sc2::ABILITY_ID::TRAIN_VIPER; 
        case sc2::UNIT_TYPEID::PROTOSS_VOIDRAY: return sc2::ABILITY_ID::TRAIN_VOIDRAY; 
        case sc2::UNIT_TYPEID::PROTOSS_ADEPT: return sc2::ABILITY_ID::TRAIN_ADEPT; 
        case sc2::UNIT_TYPEID::PROTOSS_DISRUPTOR: return sc2::ABILITY_ID::TRAIN_DISRUPTOR; 
        case sc2::UNIT_TYPEID::PROTOSS_WARPPRISM: return sc2::ABILITY_ID::TRAIN_WARPPRISM; 
        case sc2::UNIT_TYPEID::TERRAN_WIDOWMINE: return sc2::ABILITY_ID::TRAIN_WIDOWMINE; 
        case sc2::UNIT_TYPEID::PROTOSS_ZEALOT: return sc2::ABILITY_ID::TRAIN_ZEALOT; 
        case sc2::UNIT_TYPEID::ZERG_ZERGLING: return sc2::ABILITY_ID::TRAIN_ZERGLING; 

        default: return 0;
    }
}

bool Util::IsBuilding(const sc2::UnitTypeID & type)
{
    switch (type.ToType()) 
    {
        case sc2::UNIT_TYPEID::TERRAN_ARMORY:           return true; 
        case sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR:     return true; 
        case sc2::UNIT_TYPEID::ZERG_BANELINGNEST:       return true; 
        case sc2::UNIT_TYPEID::TERRAN_BARRACKS:         return true; 
        case sc2::UNIT_TYPEID::TERRAN_BARRACKSREACTOR:  return true; 
        case sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB:  return true; 
        case sc2::UNIT_TYPEID::TERRAN_BUNKER:           return true; 
        case sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER:    return true; 
        case sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE: return true; 
        case sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE:      return true; 
        case sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY:   return true; 
        case sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER:   return true; 
        case sc2::UNIT_TYPEID::ZERG_EXTRACTOR:          return true; 
        case sc2::UNIT_TYPEID::TERRAN_FACTORY:          return true; 
        case sc2::UNIT_TYPEID::TERRAN_FACTORYREACTOR:   return true; 
        case sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB:   return true; 
        case sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON:     return true; 
        case sc2::UNIT_TYPEID::PROTOSS_FORGE:           return true; 
        case sc2::UNIT_TYPEID::TERRAN_FUSIONCORE:       return true; 
        case sc2::UNIT_TYPEID::PROTOSS_GATEWAY:         return true; 
        case sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY:     return true; 
        case sc2::UNIT_TYPEID::ZERG_HATCHERY:           return true; 
        case sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN:       return true; 
        case sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT:     return true; 
        case sc2::UNIT_TYPEID::TERRAN_MISSILETURRET:    return true; 
        case sc2::UNIT_TYPEID::PROTOSS_NEXUS:           return true; 
        case sc2::UNIT_TYPEID::ZERG_NYDUSCANAL:         return true; 
        case sc2::UNIT_TYPEID::ZERG_NYDUSNETWORK:       return true; 
        case sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON:    return true; 
        case sc2::UNIT_TYPEID::PROTOSS_PYLON:           return true; 
        case sc2::UNIT_TYPEID::TERRAN_REFINERY:         return true; 
        case sc2::UNIT_TYPEID::ZERG_ROACHWARREN:        return true; 
        case sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY:     return true; 
        case sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY: return true; 
        case sc2::UNIT_TYPEID::TERRAN_SENSORTOWER:      return true; 
        case sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL:       return true; 
        case sc2::UNIT_TYPEID::ZERG_SPINECRAWLER:       return true; 
        case sc2::UNIT_TYPEID::ZERG_SPIRE:              return true; 
        case sc2::UNIT_TYPEID::ZERG_SPORECRAWLER:       return true; 
        case sc2::UNIT_TYPEID::PROTOSS_STARGATE:        return true; 
        case sc2::UNIT_TYPEID::TERRAN_STARPORT:         return true; 
        case sc2::UNIT_TYPEID::TERRAN_STARPORTREACTOR:  return true; 
        case sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB:  return true; 
        case sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT:      return true; 
        case sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE:  return true; 
        case sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL: return true; 
        case sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN:    return true; 
        case sc2::UNIT_TYPEID::ZERG_HIVE:               return true; 
        case sc2::UNIT_TYPEID::ZERG_LAIR:               return true; 
        case sc2::UNIT_TYPEID::ZERG_GREATERSPIRE:       return true; 
        case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND:   return true; 
        case sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS: return true;  

        default: return false;
    }
}

// checks where a given unit can make a given unit type now
// this is done by iterating its legal abilities for the build command to make the unit
bool Util::UnitCanBuildTypeNow(const sc2::Unit & unit, const sc2::UnitTypeID & type, CCBot & m_bot)
{
    sc2::AvailableAbilities available_abilities = m_bot.Query()->GetAbilitiesForUnit(unit.tag);
    
    // quick check if the unit can't do anything it certainly can't build the thing we want
    if (available_abilities.abilities.empty()) 
    {
        return false;
    }
    else 
    {
        // check to see if one of the unit's available abilities matches the build ability type
        sc2::AbilityID buildTypeAbility = Util::UnitTypeIDToAbilityID(type);
        for (const sc2::AvailableAbility & available_ability : available_abilities.abilities) 
        {
            if (available_ability.ability_id == buildTypeAbility)
            {
                return true;
            }
        }
    }

    return false;
}