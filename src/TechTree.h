#pragma once

#include "Common.h"

class CCBot;
class BuildType;

struct TechTreeItem
{
    sc2::Race                       race;             // the race of this item
    int                             mineralCost;      // mineral cost of the item
    int                             gasCost;          // gas cost of the item
    int                             supplyCost;       // supply cost of the item
    int                             buildTime;        // build time of the item
    sc2::AbilityID                  buildAbility;     // the ability that creates this item
    sc2::AbilityID                  warpAbility;      // the ability that creates this item via warp-in
    std::vector<sc2::UnitTypeID>    whatBuilds;       // any of these units can build the item
    std::vector<sc2::UnitTypeID>    requiredUnits;    // owning ONE of these is required to make
    std::vector<sc2::UpgradeID>     requiredUpgrades; // having ALL of these is required to make
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

    const TechTreeItem & getData(const sc2::UnitTypeID & type) const;
    const TechTreeItem & getData(const sc2::UpgradeID & type)  const;
    const TechTreeItem & getData(const BuildType & type)       const;
};