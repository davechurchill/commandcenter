#pragma once

#include "Common.h"

namespace BuildTypes
{
    enum { Unit, Upgrade, Buff, Ability, None };
}

class CCBot;
class BuildType
{
    size_t          m_type;
    std::string     m_name;
    sc2::Race       m_race;
    sc2::UnitTypeID m_unitType;
    sc2::UpgradeID  m_upgrade;
    sc2::AbilityID  m_ability;
    sc2::UnitTypeID m_whatBuilds;
    int             m_mineralCost;
    int             m_gasCost;
    int             m_supplyCost;

public:

    BuildType();
    BuildType(const std::string & name, CCBot & bot);
    BuildType(const sc2::UnitTypeID & unitType, CCBot & bot);
    BuildType(const sc2::UpgradeID & upgradeType, CCBot & bot);
    BuildType(const sc2::BuffID & buffType, CCBot & bot);
    BuildType(const sc2::AbilityID & abilityType, CCBot & bot);

    bool    isUnit()		const;
    bool    isBuff()		const;
    bool    isUpgrade()	    const;
    bool    isAbility()	    const;
    bool    isBuilding()	const;
    bool    isRefinery()	const;

    const size_t &          getBuildType() const;
    const std::string &     getName() const;
    const sc2::Race &       getRace() const;
    const sc2::UnitTypeID & getUnitTypeID() const;
    const sc2::UpgradeID &  getUpgradeID() const;
    const sc2::AbilityID &  getAbilityID() const;
    const sc2::UnitTypeID & whatBuilds() const;

    int supplyRequired();
    int mineralPrice(CCBot & bot)  const;
    int gasPrice(CCBot & bot)      const;

};