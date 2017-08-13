#include "BuildType.h"
#include "Util.h"
#include "CCBot.h"

BuildType::BuildType()
    : m_type        (BuildTypes::None)
    , m_name        ("BuildType")
    , m_race        (sc2::Race::Random)
    , m_unitType    (0)
    , m_upgrade     (0)
    , m_whatBuilds  (0)
    , m_mineralCost (0)
    , m_gasCost     (0)
    , m_supplyCost  (0)
{
}

BuildType::BuildType(const std::string & name, CCBot & bot)
    : BuildType()
{
    m_name = name;

    m_unitType = Util::GetUnitTypeIDFromName(m_name, bot);
    if (m_unitType)
    {
        *this = BuildType(m_unitType, bot);
        return;
    }

    m_upgrade = Util::GetUpgradeIDFromName(m_name, bot);
    if (m_upgrade)
    {
        *this = BuildType(m_upgrade, bot);
        return;
    }

    BOT_ASSERT(false, "Could not find BuildType with name: %s", name.c_str());
}

BuildType::BuildType(const sc2::UnitTypeID & unitType, CCBot & bot)
{
    m_type          = BuildTypes::Unit;
    m_unitType      = unitType;
    m_mineralCost   = bot.Observation()->GetUnitTypeData()[unitType].mineral_cost;
    m_gasCost       = bot.Observation()->GetUnitTypeData()[unitType].vespene_cost;
    m_supplyCost    = bot.Observation()->GetUnitTypeData()[unitType].cargo_size;
}

BuildType::BuildType(const sc2::UpgradeID & upgradeType, CCBot & bot)
{
    m_type          = BuildTypes::Upgrade;
    m_upgrade       = upgradeType;
    // m_mineralCost   = bot.Observation()->GetUpgradeData()[upgradeType];
    // m_gasCost       = bot.Observation()->GetUpgradeData()[upgradeType].vespene_cost;
    // m_supplyCost    = bot.Observation()->GetUpgradeData()[upgradeType].cargo_size;
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

bool BuildType::isBuilding() const
{
    return isUnit() && Util::IsBuilding(getUnitTypeID());
}

bool BuildType::isRefinery() const
{
    return isUnit() && Util::IsRefineryType(m_unitType);
}

bool BuildType::isWorker() const
{
    return isUnit() && Util::IsWorkerType(m_unitType);
}

bool BuildType::isTownHall() const
{
    return isUnit() && Util::IsTownHallType(m_unitType);
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