#include "Util.h"
#include "CCBot.h"
#include <iostream>

std::string Util::GetStringFromRace(const CCRace & race)
{
#ifdef SC2API
    if      (race == sc2::Race::Terran)  { return "Terran"; }
    else if (race == sc2::Race::Protoss) { return "Protoss"; }
    else if (race == sc2::Race::Zerg)    { return "Zerg"; }
    else if (race == sc2::Race::Random)  { return "Random"; }
#else
    BWAPI::Race race = type.getRace();
    if      (race == BWAPI::Races::Terran)  { return "Terran"; }
    else if (race == BWAPI::Races::Protoss) { return "Protoss"; }
    else if (race == BWAPI::Races::Zerg)    { return "Zerg"; }
    else if (race == BWAPI::Races::Unknown) { return "Unknown"; }
#endif
    BOT_ASSERT(false, "Unknown Race");
    return "Error";
}

CCRace Util::GetRaceFromString(const std::string & raceIn)
{
    std::string race(raceIn);
    std::transform(race.begin(), race.end(), race.begin(), ::tolower);

#ifdef SC2API
    if      (race == "terran")  { return sc2::Race::Terran; }
    else if (race == "protoss") { return sc2::Race::Protoss; }
    else if (race == "zerg")    { return sc2::Race::Zerg; }
    else if (race == "random")  { return sc2::Race::Random; }
    
    BOT_ASSERT(false, "Unknown Race: ", race.c_str());
    return sc2::Race::Random;
#else
    if      (race == "terran")  { return BWAPI::Races::Terran; }
    else if (race == "protoss") { return BWAPI::Races::Protoss; }
    else if (race == "zerg")    { return BWAPI::Races::Zerg; }
    else if (race == "random")  { return BWAPI::Races::Unknown; }

    BOT_ASSERT(false, "Unknown Race: ", race.c_str());
    return BWAPI::Races::Unknown;
#endif
}

CCRace Util::GetRace(CCUnit unit, CCBot & bot)
{
    return GetRace(GetType(unit), bot);
}

CCRace Util::GetRace(const CCUnitType & type, CCBot & bot)
{
#ifdef SC2API
    return bot.Observation()->GetUnitTypeData()[type].race;
#else
    return type.getRace();
#endif
}


CCUnitType Util::GetType(CCUnit unit)
{
#ifdef SC2API
    return unit->unit_type;
#else
    return unit->getType();
#endif
}

CCUnitID Util::GetID(CCUnit unit)
{
#ifdef SC2API
    return unit->tag;
#else
    return unit->getID();
#endif
}

bool Util::IsTownHall(CCUnit unit)
{
    BOT_ASSERT(unit, "Unit pointer was null");
    return IsTownHallType(GetType(unit));
}

bool Util::IsTownHallType(const CCUnitType & type)
{
#ifdef SC2API
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
#else

#endif
}

bool Util::IsRefinery(CCUnit unit)
{
    BOT_ASSERT(unit, "Unit pointer was null");
    return IsRefineryType(GetType(unit));
}

bool Util::IsRefineryType(const CCUnitType & type)
{
    switch (type.ToType()) 
    {
        case sc2::UNIT_TYPEID::TERRAN_REFINERY      : return true;
        case sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR  : return true;
        case sc2::UNIT_TYPEID::ZERG_EXTRACTOR       : return true;
        default: return false;
    }
}

bool Util::IsGeyser(CCUnit unit)
{
    BOT_ASSERT(unit, "Unit pointer was null");
    return IsGeyserType(GetType(unit));
}

bool Util::IsGeyserType(const CCUnitType & type)
{
    switch (type.ToType()) 
    {
        case sc2::UNIT_TYPEID::NEUTRAL_VESPENEGEYSER        : return true;
        case sc2::UNIT_TYPEID::NEUTRAL_PROTOSSVESPENEGEYSER : return true;
        case sc2::UNIT_TYPEID::NEUTRAL_SPACEPLATFORMGEYSER  : return true;
        default: return false;
    }
}

bool Util::IsMineral(CCUnit unit)
{
    BOT_ASSERT(unit, "Unit pointer was null");
    return IsMineralType(GetType(unit));
}

bool Util::IsMineralType(const CCUnitType & type)
{
#ifdef SC2API
    switch (type.ToType()) 
    {
        case sc2::UNIT_TYPEID::NEUTRAL_MINERALFIELD         : return true;
        case sc2::UNIT_TYPEID::NEUTRAL_MINERALFIELD750      : return true;
        case sc2::UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD     : return true;
        case sc2::UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD750  : return true;
        default: return false;
    }
#else

#endif
}

bool Util::IsWorker(CCUnit unit)
{
    BOT_ASSERT(unit, "Unit pointer was null");
    return IsWorkerType(GetType(unit));
}

bool Util::IsWorkerType(const CCUnitType & unit)
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

CCUnitType Util::GetSupplyProvider(const sc2::Race & race)
{
    switch (race) 
    {
        case sc2::Race::Terran: return sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT;
        case sc2::Race::Protoss: return sc2::UNIT_TYPEID::PROTOSS_PYLON;
        case sc2::Race::Zerg: return sc2::UNIT_TYPEID::ZERG_OVERLORD;
        default: return 0;
    }
}

CCUnitType Util::GetTownHall(const sc2::Race & race)
{
    switch (race) 
    {
        case sc2::Race::Terran: return sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER;
        case sc2::Race::Protoss: return sc2::UNIT_TYPEID::PROTOSS_NEXUS;
        case sc2::Race::Zerg: return sc2::UNIT_TYPEID::ZERG_HATCHERY;
        default: return 0;
    }
}

bool Util::IsCompleted(CCUnit unit)
{
    BOT_ASSERT(unit, "Unit pointer was null");
    return unit->build_progress == 1.0f;
}

bool Util::IsIdle(CCUnit unit)
{
    BOT_ASSERT(unit, "Unit pointer was null");
    return unit->orders.empty();
}

int Util::GetUnitTypeMineralPrice(const CCUnitType type, const CCBot & bot)
{
    return bot.Observation()->GetUnitTypeData()[type].mineral_cost;
}

int Util::GetUnitTypeGasPrice(const CCUnitType type, const CCBot & bot)
{
    return bot.Observation()->GetUnitTypeData()[type].vespene_cost;
}

int Util::GetUnitTypeWidth(const CCUnitType type, const CCBot & bot)
{
    return (int)(2 * bot.Observation()->GetAbilityData()[bot.Data(type).buildAbility].footprint_radius);
}

int Util::GetUnitTypeHeight(const CCUnitType type, const CCBot & bot)
{
    return (int)(2 * bot.Observation()->GetAbilityData()[bot.Data(type).buildAbility].footprint_radius);
}


CCPosition Util::CalcCenter(const std::vector<CCUnit> & units)
{
    if (units.empty())
    {
        return CCPosition(0.0f,0.0f);
    }

    float cx = 0.0f;
    float cy = 0.0f;

    for (auto unit : units)
    {
        BOT_ASSERT(unit, "Unit pointer was null");
        cx += unit->pos.x;
        cy += unit->pos.y;
    }

    return CCPosition(cx / units.size(), cy / units.size());
}

bool Util::IsDetector(CCUnit unit)
{
    BOT_ASSERT(unit, "Unit pointer was null");
    return IsDetectorType(unit->unit_type);
}

float Util::GetAttackRange(const CCUnitType & type, CCBot & bot)
{
#ifdef SC2API
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
#else

#endif
}

bool Util::IsDetectorType(const CCUnitType & type)
{
    switch (type.ToType())
    {
        case sc2::UNIT_TYPEID::PROTOSS_OBSERVER        : return true;
        case sc2::UNIT_TYPEID::ZERG_OVERSEER           : return true;
        case sc2::UNIT_TYPEID::TERRAN_MISSILETURRET    : return true;
        case sc2::UNIT_TYPEID::ZERG_SPORECRAWLER       : return true;
        case sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON    : return true;
        case sc2::UNIT_TYPEID::TERRAN_RAVEN            : return true;
        default: return false;
    }
}

CCPlayer Util::GetPlayer(CCUnit unit)
{
    BOT_ASSERT(unit, "Unit pointer was null");
    if (unit->alliance == sc2::Unit::Alliance::Self)
    {
        return 0;
    }

    if (unit->alliance == sc2::Unit::Alliance::Enemy)
    {
        return 1;
    }

    if (unit->alliance == sc2::Unit::Alliance::Neutral)
    {
        return 2;
    }

    return -1;
}

bool Util::IsCombatUnitType(const CCUnitType & type, CCBot & bot)
{
    if (IsWorkerType(type)) { return false; }
    if (IsSupplyProviderType(type)) { return false; }
    if (bot.Data(type).isBuilding) { return false; }

    if (type == sc2::UNIT_TYPEID::ZERG_EGG) { return false; }
    if (type == sc2::UNIT_TYPEID::ZERG_LARVA) { return false; }

    return true;
}

bool Util::IsCombatUnit(CCUnit unit, CCBot & bot)
{
    BOT_ASSERT(unit, "Unit pointer was null");
    return IsCombatUnitType(GetType(unit), bot);
}

bool Util::IsSupplyProvider(CCUnit unit)
{
    BOT_ASSERT(unit, "Unit pointer was null");
    return IsSupplyProviderType(unit->unit_type);
}

bool Util::IsSupplyProviderType(const CCUnitType & type)
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

float Util::Dist(const CCPosition & p1, const CCPosition & p2)
{
    return sqrtf(Util::DistSq(p1,p2));
}

float Util::DistSq(const CCPosition & p1, const CCPosition & p2)
{
    float dx = p1.x - p2.x;
    float dy = p1.y - p2.y;

    return dx*dx + dy*dy;
}

CCUnitType Util::GetUnitTypeFromName(const std::string & name, CCBot & bot)
{
#ifdef SC2API
    for (const sc2::UnitTypeData & data : bot.Observation()->GetUnitTypeData())
    {
        if (name == data.name)
        {
            return data.unit_type_id;
        }
    }
#else

#endif

    return 0;
}

sc2::UpgradeID Util::GetUpgradeFromName(const std::string & name, CCBot & bot)
{
#ifdef SC2API
    for (const sc2::UpgradeData & data : bot.Observation()->GetUpgradeData())
    {
        if (name == data.name)
        {
            return data.upgrade_id;
        }
    }

    return 0;
#else

#endif
}

#ifdef SC2API
sc2::BuffID Util::GetBuffFromName(const std::string & name, CCBot & bot)
{
    for (const sc2::BuffData & data : bot.Observation()->GetBuffData())
    {
        if (name == data.name)
        {
            return data.buff_id;
        }
    }

    return 0;
}

sc2::AbilityID Util::GetAbilityFromName(const std::string & name, CCBot & bot)
{
    for (const sc2::AbilityData & data : bot.Observation()->GetAbilityData())
    {
        if (name == data.link_name)
        {
            return data.ability_id;
        }
    }

    return 0;
}
#endif

// checks where a given unit can make a given unit type now
// this is done by iterating its legal abilities for the build command to make the unit
bool Util::UnitCanBuildTypeNow(CCUnit unit, const CCUnitType & type, CCBot & m_bot)
{
    BOT_ASSERT(unit, "Unit pointer was null");
    sc2::AvailableAbilities available_abilities = m_bot.Query()->GetAbilitiesForUnit(unit);
    
    // quick check if the unit can't do anything it certainly can't build the thing we want
    if (available_abilities.abilities.empty()) 
    {
        return false;
    }
    else 
    {
        // check to see if one of the unit's available abilities matches the build ability type
        sc2::AbilityID buildTypeAbility = m_bot.Data(type).buildAbility;
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
