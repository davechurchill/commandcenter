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

CCPositionType Util::TileToPosition(float tile)
{
#ifdef SC2API
    return tile;
#else
    return (int)(tile * 32);
#endif
}

UnitType Util::GetSupplyProvider(const CCRace & race, CCBot & bot)
{
#ifdef SC2API
    switch (race) 
    {
        case sc2::Race::Terran: return UnitType(sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT, bot);
        case sc2::Race::Protoss: return UnitType(sc2::UNIT_TYPEID::PROTOSS_PYLON, bot);
        case sc2::Race::Zerg: return UnitType(sc2::UNIT_TYPEID::ZERG_OVERLORD, bot);
        default: return UnitType();
    }
#else
    return UnitType(race.getSupplyProvider(), bot);
#endif
}

UnitType Util::GetTownHall(const CCRace & race, CCBot & bot)
{
#ifdef SC2API
    switch (race) 
    {
        case sc2::Race::Terran: return UnitType(sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER, bot);
        case sc2::Race::Protoss: return UnitType(sc2::UNIT_TYPEID::PROTOSS_NEXUS, bot);
        case sc2::Race::Zerg: return UnitType(sc2::UNIT_TYPEID::ZERG_HATCHERY, bot);
        default: return UnitType();
    }
#else
    return UnitType(race.getResourceDepot(), bot);
#endif
}

UnitType Util::GetRefinery(const CCRace & race, CCBot & bot)
{
#ifdef SC2API
    switch (race) 
    {
        case sc2::Race::Terran: return UnitType(sc2::UNIT_TYPEID::TERRAN_REFINERY, bot);
        case sc2::Race::Protoss: return UnitType(sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR, bot);
        case sc2::Race::Zerg: return UnitType(sc2::UNIT_TYPEID::ZERG_EXTRACTOR, bot);
        default: return UnitType();
    }
#else
    return UnitType(race.getRefinery(), bot);
#endif
}

CCPosition Util::CalcCenter(const std::vector<Unit> & units)
{
    if (units.empty())
    {
        return CCPosition(0, 0);
    }

    CCPositionType cx = 0;
    CCPositionType cy = 0;

    for (auto & unit : units)
    {
        BOT_ASSERT(unit.isValid(), "Unit pointer was null");
        cx += unit.getPosition().x;
        cy += unit.getPosition().y;
    }

    return CCPosition(cx / units.size(), cy / units.size());
}

bool Util::IsZerg(const CCRace & race)
{
#ifdef SC2API
    return race == sc2::Race::Zerg;
#else
    return race == BWAPI::Races::Zerg;
#endif
}

bool Util::IsProtoss(const CCRace & race)
{
#ifdef SC2API
    return race == sc2::Race::Protoss;
#else
    return race == BWAPI::Races::Protoss;
#endif
}

bool Util::IsTerran(const CCRace & race)
{
#ifdef SC2API
    return race == sc2::Race::Terran;
#else
    return race == BWAPI::Races::Terran;
#endif
}

CCTilePosition Util::GetTilePosition(const CCPosition & pos)
{
#ifdef SC2API
    return CCTilePosition((int)std::floor(pos.x), (int)std::floor(pos.y));
#else
    return CCTilePosition(pos);
#endif
}

CCPosition Util::GetPosition(const CCTilePosition & tile)
{
#ifdef SC2API
    return CCPosition((float)tile.x, (float)tile.y);
#else
    return CCPosition(tile);
#endif
}

float Util::Dist(const CCPosition & p1, const CCPosition & p2)
{
    return sqrtf((float)Util::DistSq(p1,p2));
}

float Util::Dist(const Unit & unit, const CCPosition & p2)
{
    return Dist(unit.getPosition(), p2);
}

float Util::Dist(const Unit & unit1, const Unit & unit2)
{
    return Dist(unit1.getPosition(), unit2.getPosition());
}

CCPositionType Util::DistSq(const CCPosition & p1, const CCPosition & p2)
{
    CCPositionType dx = p1.x - p2.x;
    CCPositionType dy = p1.y - p2.y;

    return dx*dx + dy*dy;
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
bool Util::UnitCanMetaTypeNow(const Unit & unit, const UnitType & type, CCBot & m_bot)
{
#ifdef SC2API
    BOT_ASSERT(unit.isValid(), "Unit pointer was null");
    sc2::AvailableAbilities available_abilities = m_bot.Query()->GetAbilitiesForUnit(unit.getUnitPtr());
    
    // quick check if the unit can't do anything it certainly can't build the thing we want
    if (available_abilities.abilities.empty()) 
    {
        return false;
    }
    else 
    {
        // check to see if one of the unit's available abilities matches the build ability type
        sc2::AbilityID MetaTypeAbility = m_bot.Data(type).buildAbility;
        for (const sc2::AvailableAbility & available_ability : available_abilities.abilities) 
        {
            if (available_ability.ability_id == MetaTypeAbility)
            {
                return true;
            }
        }
    }
#else

#endif
    return false;
}
