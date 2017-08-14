#pragma once

#include "Common.h"

class CCBot;
class BuildType;

struct TechTreeItem
{
    sc2::Race                    m_race;            // the race of this item
    sc2::AbilityID               m_buildAbility;    // the ability that creates this item
    sc2::AbilityID               m_warpAbility;    // the ability that creates this item via warp-in
    std::vector<sc2::UnitTypeID> m_whatBuilds;      // any of these units can build the item
    std::vector<sc2::UnitTypeID> m_requiredUnits;     // owning ONE of these is required to make
    std::vector<sc2::UpgradeID>  m_requiredUpgrades;  // having ALL of these is required to make
};

class TechTree
{
    CCBot & m_bot;
    std::map<sc2::UnitTypeID, TechTreeItem> m_unitTypeData;
    std::map<sc2::UpgradeID, TechTreeItem>  m_upgradeData;

    void initUnitTypeData();
    void initUpgradeData();

public:

    TechTree(CCBot & bot);

    const std::vector<sc2::UnitTypeID> &    getWhatBuilds(const sc2::UnitTypeID & type) const;
    const std::vector<sc2::UnitTypeID> &    getRequiredUnits(const sc2::UnitTypeID & type) const;
    const std::vector<sc2::UpgradeID> &     getRequiredUpgrades(const sc2::UnitTypeID & type) const;
    const sc2::AbilityID &                  getBuildAbility(const sc2::UnitTypeID & type) const;
    const sc2::AbilityID &                  getWarpAbility(const sc2::UnitTypeID & type) const;

    const std::vector<sc2::UnitTypeID> &    getWhatBuilds(const sc2::UpgradeID & type) const;
    const std::vector<sc2::UnitTypeID> &    getRequiredUnits(const sc2::UpgradeID & type) const;
    const std::vector<sc2::UpgradeID> &     getRequiredUpgrades(const sc2::UpgradeID & type) const;
    const sc2::AbilityID &                  getBuildAbility(const sc2::UpgradeID & type) const;
    const sc2::AbilityID &                  getWarpAbility(const sc2::UpgradeID & type) const;

    const std::vector<sc2::UnitTypeID> &    getWhatBuilds(const BuildType & type) const;
    const std::vector<sc2::UnitTypeID> &    getRequiredUnits(const BuildType & type) const;
    const std::vector<sc2::UpgradeID> &     getRequiredUpgrades(const BuildType & type) const;
    const sc2::AbilityID &                  getBuildAbility(const BuildType & type) const;
    const sc2::AbilityID &                  getWarpAbility(const BuildType & type) const;
};