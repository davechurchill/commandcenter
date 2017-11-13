#include "MetaType.h"
#include "Util.h"
#include "CCBot.h"

MetaType::MetaType()
    : m_bot         (nullptr)
    , m_type        (MetaTypes::None)
    , m_name        ("MetaType")
    , m_unitType    ()
    , m_upgrade     ()
{
}

#ifdef SC2API
MetaType::MetaType(const std::string & name, CCBot & bot)
    : MetaType()
{
    m_bot = &bot;
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
    : MetaType()
{
    m_bot = &bot;

    std::string inputName(name);
    std::replace(inputName.begin(), inputName.end(), '_', ' ');

    for (const BWAPI::UnitType & unitType : BWAPI::UnitTypes::allUnitTypes())
    {
        // check to see if the names match exactly
        std::string typeName = unitType.getName();
        std::replace(typeName.begin(), typeName.end(), '_', ' ');
        if (typeName == inputName)
        {
            *this = MetaType(UnitType(unitType, bot), bot);
            return;
        }

        // check to see if the names match without the race prefix
        const std::string & raceName = unitType.getRace().getName();
        if ((typeName.length() > raceName.length()) && (typeName.compare(raceName.length() + 1, typeName.length(), inputName) == 0))
        {
            *this = MetaType(UnitType(unitType, bot), bot);
            return;
        }
    }

    for (const BWAPI::TechType & techType : BWAPI::TechTypes::allTechTypes())
    {
        std::string typeName = techType.getName();
        std::replace(typeName.begin(), typeName.end(), '_', ' ');
        if (typeName == inputName)
        {
            *this = MetaType(techType, bot);
            return;
        }
    }

    for (const BWAPI::UpgradeType & upgradeType : BWAPI::UpgradeTypes::allUpgradeTypes())
    {
        std::string typeName = upgradeType.getName();
        std::replace(typeName.begin(), typeName.end(), '_', ' ');
        if (typeName == inputName)
        {
            *this = MetaType(upgradeType, bot);
            return;
        }
    }

    BOT_ASSERT(false, "Could not find MetaType with name: %s", name.c_str());
}

MetaType::MetaType(const BWAPI::TechType & t, CCBot & bot) 
    : m_tech(t)
    , m_type(MetaTypes::Tech) 
    , m_race(t.getRace())
    , m_name(t.getName())
    , m_bot(&bot)
{
}
#endif


MetaType::MetaType(const UnitType & unitType, CCBot & bot)
{
    m_bot           = &bot;
    m_type          = MetaTypes::Unit;
    m_unitType      = unitType;
    m_race          = unitType.getRace();
    m_name          = unitType.getName();
}

MetaType::MetaType(const CCUpgrade & upgradeType, CCBot & bot)
{
    m_bot           = &bot;
    m_type          = MetaTypes::Upgrade;
    m_upgrade       = upgradeType;

#ifdef SC2API
    m_race          = m_bot->GetPlayerRace(Players::Self);
    m_name          = sc2::UpgradeIDToName(upgradeType);
#else
    m_race          = upgradeType.getRace();
    m_name          = upgradeType.getName();
#endif
}

bool MetaType::isBuilding() const
{
    return isUnit() && getUnitType().isBuilding();
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