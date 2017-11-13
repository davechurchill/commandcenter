#pragma once

#include "Common.h"
#include "UnitType.h"

class CCBot;

class Unit
{
    mutable CCBot * m_bot;
    CCUnitID    m_unitID;
    UnitType    m_unitType;

#ifdef SC2API
    const sc2::Unit * m_unit;
#else
    BWAPI::Unit m_unit;
#endif

public:

    Unit();

#ifdef SC2API
    Unit(const sc2::Unit * unit, CCBot & bot);
    const sc2::Unit * getUnitPtr() const;
    const sc2::UnitTypeID & getAPIUnitType() const;
#else
    Unit(const BWAPI::Unit unit, CCBot & bot);
    const BWAPI::Unit getUnitPtr() const;
    const BWAPI::UnitType & getAPIUnitType() const;
#endif

    bool operator < (const Unit & rhs) const;
    bool operator == (const Unit & rhs) const;

    const UnitType & getType() const;

    CCPosition getPosition() const;
    CCTilePosition getTilePosition() const;
    CCHealth getHitPoints() const;
    CCHealth getShields() const;
    CCHealth getEnergy() const;
    CCPlayer getPlayer() const;
    CCUnitID getID() const;
    float getBuildPercentage() const;
    int getWeaponCooldown() const;
    bool isCompleted() const;
    bool isBeingConstructed() const;
    bool isCloaked() const;
    bool isFlying() const;
    bool isAlive() const;
    bool isPowered() const;
    bool isIdle() const;
    bool isBurrowed() const;
    bool isValid() const;
    bool isTraining() const;
    bool isConstructing(const UnitType & type) const;

    void stop           () const;
    void attackUnit     (const Unit & target) const;
    void attackMove     (const CCPosition & targetPosition) const;
    void move           (const CCPosition & targetPosition) const;
    void move           (const CCTilePosition & targetTilePosition) const;
    void rightClick     (const Unit & target) const;
    void repair         (const Unit & target) const;
    void build          (const UnitType & buildingType, CCTilePosition pos) const;
    void buildTarget    (const UnitType & buildingType, const Unit & target) const;
    void train          (const UnitType & buildingType) const;
    void morph          (const UnitType & type) const;
};
