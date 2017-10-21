#include "UnitType.h"
#include "CCBot.h"

UnitType::UnitType()
    : m_bot(nullptr)
    , m_type(0)
{

}

#ifdef SC2API
UnitType::UnitType(sc2::UnitTypeID type, CCBot & bot)
    : m_bot(&bot)
    , m_type(type)
{
    
}

sc2::UnitTypeID UnitType::getAPIUnitType() const
{
    return m_type;
}

#else
UnitType::UnitType(BWAPI::UnitType type, CCBot & bot)
    : m_bot(&bot)
    , m_type(type)
{
    
}

BWAPI::UnitType Unit::getAPIUnitType() const
{
    return m_type;
}

#endif
bool UnitType::operator < (const UnitType & rhs) const
{
    return m_type < rhs.m_type;
}

bool UnitType::operator == (const UnitType & rhs) const
{
    return m_type == rhs.m_type;
}

bool UnitType::isValid() const
{
    return m_type != 0;
}

std::string UnitType::getName() const
{
#ifdef SC2API
    return sc2::UnitTypeToName(m_type);
#else
    return m_type.getName();
#endif
}

CCRace UnitType::getRace() const
{
#ifdef SC2API
    return m_bot->Observation()->GetUnitTypeData()[m_type].race;
#else
    return getType().getRace();
#endif
}

bool UnitType::isCombatUnit() const
{
#ifdef SC2API
    if (isWorker()) { return false; }
    if (isSupplyProvider()) { return false; }
    if (isBuilding()) { return false; }

    if (getAPIUnitType() == sc2::UNIT_TYPEID::ZERG_EGG) { return false; }
    if (getAPIUnitType() == sc2::UNIT_TYPEID::ZERG_LARVA) { return false; }

    return true;
#else
    // check for various types of combat units
    if (m_type.canAttack() || 
        m_type == BWAPI::UnitTypes::Terran_Medic ||
        m_type == BWAPI::UnitTypes::Protoss_High_Templar ||
        m_type == BWAPI::UnitTypes::Protoss_Observer ||
        m_type == BWAPI::UnitTypes::Zerg_Overlord ||
        m_type == BWAPI::UnitTypes::Protoss_Observer)
    {
        return true;
    }

    // no workers or buildings allowed
    if (m_type.isWorker() || m_type.isBuilding())
    {
        return false;
    }

    return false;
#endif
}

bool UnitType::isSupplyProvider() const
{
    return (supplyProvided() < 0) && !isResourceDepot();
}

bool UnitType::isResourceDepot() const
{
#ifdef SC2API
    switch (m_type.ToType()) 
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
    return type.isResourceDepot();
#endif
}

bool UnitType::isRefinery() const
{
#ifdef SC2API
    switch (m_type.ToType()) 
    {
        case sc2::UNIT_TYPEID::TERRAN_REFINERY      : return true;
        case sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR  : return true;
        case sc2::UNIT_TYPEID::ZERG_EXTRACTOR       : return true;
        default: return false;
    }
#else
    return type.isRefinery();
#endif
}

bool UnitType::isDetector() const
{
#ifdef SC2API
    switch (m_type.ToType())
    {
        case sc2::UNIT_TYPEID::PROTOSS_OBSERVER        : return true;
        case sc2::UNIT_TYPEID::ZERG_OVERSEER           : return true;
        case sc2::UNIT_TYPEID::TERRAN_MISSILETURRET    : return true;
        case sc2::UNIT_TYPEID::ZERG_SPORECRAWLER       : return true;
        case sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON    : return true;
        case sc2::UNIT_TYPEID::TERRAN_RAVEN            : return true;
        default: return false;
    }
#else
    return m_type.isDetector();
#endif
}

bool UnitType::isGeyser() const
{
#ifdef SC2API
    switch (m_type.ToType()) 
    {
        case sc2::UNIT_TYPEID::NEUTRAL_VESPENEGEYSER        : return true;
        case sc2::UNIT_TYPEID::NEUTRAL_PROTOSSVESPENEGEYSER : return true;
        case sc2::UNIT_TYPEID::NEUTRAL_SPACEPLATFORMGEYSER  : return true;
        default: return false;
    }
#else
    return type.isGeyser();
#endif
}

bool UnitType::isMineral() const
{
#ifdef SC2API
    switch (m_type.ToType()) 
    {
        case sc2::UNIT_TYPEID::NEUTRAL_MINERALFIELD         : return true;
        case sc2::UNIT_TYPEID::NEUTRAL_MINERALFIELD750      : return true;
        case sc2::UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD     : return true;
        case sc2::UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD750  : return true;
        default: return false;
    }
#else
    return m_type.isMineralField();
#endif
}

bool UnitType::isWorker() const
{
#ifdef SC2API
    switch (m_type.ToType()) 
    {
        case sc2::UNIT_TYPEID::TERRAN_SCV           : return true;
        case sc2::UNIT_TYPEID::PROTOSS_PROBE        : return true;
        case sc2::UNIT_TYPEID::ZERG_DRONE           : return true;
        case sc2::UNIT_TYPEID::ZERG_DRONEBURROWED   : return true;
        default: return false;
    }
#else
    return type.isWorker();
#endif
}

float UnitType::getAttackRange() const
{
#ifdef SC2API
    auto & weapons = m_bot->Observation()->GetUnitTypeData()[m_type].weapons;
    
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
    // BWAPI
#endif
}

int UnitType::tileWidth() const
{
#ifdef SC2API
    return (int)(2 * m_bot->Observation()->GetAbilityData()[m_bot->Data(*this).buildAbility].footprint_radius);
#else
    return m_type.tileWidth();
#endif
}

int UnitType::tileHeight() const
{
#ifdef SC2API
    return (int)(2 * m_bot->Observation()->GetAbilityData()[m_bot->Data(*this).buildAbility].footprint_radius);
#else
    return m_type.tileHeight();
#endif
}

bool UnitType::isAddon() const
{
#ifdef SC2API
    return m_bot->Data(*this).isAddon;
#else
    return m_type.isAddon();
#endif
}

bool UnitType::isBuilding() const
{
#ifdef SC2API
    return m_bot->Data(*this).isBuilding;
#else
    return m_type.isBuilding();
#endif
}

int UnitType::supplyProvided() const
{
#ifdef SC2API
    return (int)m_bot->Observation()->GetUnitTypeData()[m_type].food_provided;
#else
    return m_type.supplyProvided();
#endif
}

int UnitType::supplyRequired() const
{
#ifdef SC2API
    return (int)m_bot->Observation()->GetUnitTypeData()[m_type].food_required;
#else
    return m_type.supplyRequired();
#endif
}