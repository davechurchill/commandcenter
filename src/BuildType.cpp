#include "BuildType.h"
#include "Util.h"
#include "CCBot.h"

BuildType::BuildType()
    : m_type        (BuildTypes::None)
    , m_name        ("BuildType")
    , m_race        (sc2::Race::Random)
    , m_unitType    (0)
    , m_upgrade     (0)
{
}

BuildType::BuildType(const std::string & name, CCBot & bot)
    : BuildType()
{
    m_name = name;

    m_unitType = Util::GetUnitTypeIDFromName(m_name, bot);
    if (m_unitType)
    {
        m_type = BuildTypes::Unit;
        return;
    }

    m_upgrade = Util::GetUpgradeIDFromName(m_name, bot);
    if (m_upgrade)
    {
        m_type = BuildTypes::Upgrade;
        return;
    }

    BOT_ASSERT(false, "Could not find BuildType with name: %s", name.c_str());
}

BuildType::BuildType(const sc2::UnitTypeID & unitType)
{
    m_type          = BuildTypes::Unit;
    m_unitType      = unitType;
}

BuildType::BuildType(const sc2::UpgradeID & upgradeType)
{
    m_type          = BuildTypes::Upgrade;
    m_upgrade       = upgradeType;
}

const size_t & BuildType::getBuildType() const
{
    return m_type;
}

bool BuildType::isUnit() const
{
    return m_type == BuildTypes::Unit;
}

bool BuildType::isUpgrade() const
{
    return m_type == BuildTypes::Upgrade;
}

const sc2::Race & BuildType::getRace() const
{
    return m_race;
}

const sc2::UnitTypeID & BuildType::getUnitTypeID() const
{
    return m_unitType;
}

const sc2::UpgradeID & BuildType::getUpgradeID() const
{
    return m_upgrade;
}

const std::string & BuildType::getName() const
{
    return m_name;
}