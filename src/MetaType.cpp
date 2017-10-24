#include "MetaType.h"
#include "Util.h"
#include "CCBot.h"

MetaType::MetaType()
    : m_type        (MetaTypes::None)
    , m_name        ("MetaType")
    , m_unitType    ()
    , m_upgrade     ()
{
}

#ifdef SC2API
MetaType::MetaType(const std::string & name, CCBot & bot)
    : MetaType()
{
    m_name = name;

    m_unitType = UnitType::GetUnitTypeFromName(m_name, bot);
    if (m_unitType.isValid())
    {
        m_type = MetaTypes::Unit;
        return;
    }

    for (const sc2::UpgradeData & data : bot.Observation()->GetUpgradeData())
    {
        if (name == data.name)
        {
            m_upgrade = data.upgrade_id;
            m_type = MetaTypes::Upgrade;
            return;
        }
    }

    BOT_ASSERT(false, "Could not find MetaType with name: %s", name.c_str());
}
#else
   MetaType::MetaType(const std::string & name, CCBot & bot)
    : m_type(MetaTypes::None) 
    , m_race(BWAPI::Races::None)
{
    std::string inputName(name);
    std::replace(inputName.begin(), inputName.end(), '_', ' ');

    for (const BWAPI::UnitType & unitType : BWAPI::UnitTypes::allUnitTypes())
    {
        // check to see if the names match exactly
        std::string typeName = unitType.getName();
        std::replace(typeName.begin(), typeName.end(), '_', ' ');
        if (typeName == inputName)
        {
            *this = MetaType(UnitType(unitType, bot));
            return;
        }

        // check to see if the names match without the race prefix
        const std::string & raceName = unitType.getRace().getName();
        if ((typeName.length() > raceName.length()) && (typeName.compare(raceName.length() + 1, typeName.length(), inputName) == 0))
        {
            *this = MetaType(UnitType(unitType, bot));
            return;
        }
    }

    for (const BWAPI::TechType & techType : BWAPI::TechTypes::allTechTypes())
    {
        std::string typeName = techType.getName();
        std::replace(typeName.begin(), typeName.end(), '_', ' ');
        if (typeName == inputName)
        {
            *this = MetaType(techType);
            return;
        }
    }

    for (const BWAPI::UpgradeType & upgradeType : BWAPI::UpgradeTypes::allUpgradeTypes())
    {
        std::string typeName = upgradeType.getName();
        std::replace(typeName.begin(), typeName.end(), '_', ' ');
        if (typeName == inputName)
        {
            *this = MetaType(upgradeType);
            return;
        }
    }

    BOT_ASSERT(false, "Could not find MetaType with name: %s", name.c_str());
}
#endif


MetaType::MetaType(const UnitType & unitType)
{
    m_type          = MetaTypes::Unit;
    m_unitType      = unitType;
}

MetaType::MetaType(const CCUpgrade & upgradeType)
{
    m_type          = MetaTypes::Upgrade;
    m_upgrade       = upgradeType;
}

const size_t & MetaType::getMetaType() const
{
    return m_type;
}

bool MetaType::isUnit() const
{
    return m_type == MetaTypes::Unit;
}

bool MetaType::isUpgrade() const
{
    return m_type == MetaTypes::Upgrade;
}

bool MetaType::isTech() const
{
    return m_type == MetaTypes::Tech;
}

const CCRace & MetaType::getRace() const
{
    return m_race;
}

const UnitType & MetaType::getUnitType() const
{
    return m_unitType;
}

const CCUpgrade & MetaType::getUpgrade() const
{
    return m_upgrade;
}

const std::string & MetaType::getName() const
{
    return m_name;
}

#ifndef SC2API
const BWAPI::TechType & MetaType::getTechType() const
{
    return m_tech;
}
#endif