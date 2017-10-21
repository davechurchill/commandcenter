#pragma once

#include "Common.h"
#include "UnitType.h"

class CCBot;
class BuildType;

struct UnitTypeData
{
    sc2::Race                       race            = sc2::Race::Random;             // the race of this item
    int                             mineralCost     = 0;      // mineral cost of the item
    int                             gasCost         = 0;          // gas cost of the item
    int                             supplyCost      = 0;       // supply cost of the item
    int                             buildTime       = 0;        // build time of the item
    bool                            isUnit          = false;
    bool                            isBuilding      = false;
    bool                            isWorker        = false;
    bool                            isRefinery      = false;
    bool                            isSupplyDepot   = false;
    bool                            isTownHall      = false;
    bool                            isAddon         = false;
    sc2::AbilityID                  buildAbility    = 0;     // the ability that creates this item
    sc2::AbilityID                  warpAbility     = 0;      // the ability that creates this item via warp-in
    std::vector<sc2::UnitTypeID>           whatBuilds;       // any of these units can build the item
    std::vector<sc2::UnitTypeID>           requiredUnits;    // owning ONE of these is required to make
    std::vector<sc2::UpgradeID>     requiredUpgrades; // having ALL of these is required to make
};

class TechTree
{
    CCBot & m_bot;
    std::map<sc2::UnitTypeID, UnitTypeData> m_unitTypeData;
    std::map<sc2::UpgradeID, UnitTypeData>  m_upgradeData;

    void initUnitTypeData();
    void initUpgradeData();

    void outputJSON(const std::string & filename) const;

public:

    TechTree(CCBot & bot);
    void onStart();

    const UnitTypeData & getData(const UnitType & type) const;
    const UnitTypeData & getData(const sc2::UpgradeID & type)  const;
    const UnitTypeData & getData(const BuildType & type)       const;
};