#pragma once

#include "Common.h"

class CCBot;

class Unit
{
    mutable CCBot * m_bot;
    CCUnitID    m_unitID;

#ifdef SC2API
    const sc2::Unit * m_unit;
#else
    const BWAPI::Unit m_unit;
#endif

public:

    Unit();

#ifdef SC2API
    Unit(const sc2::Unit * unit, CCBot & bot);
    const sc2::Unit * getUnitPtr() const;
#else
    Unit(const BWAPI::Unit unit, CCBot & bot);
    const BWAPI::Unit getUnitPtr() const;
#endif

    bool operator < (const Unit & rhs) const;
    bool operator == (const Unit & rhs) const;

    const CCUnitType & getType() const;
    const CCRace & getRace() const;

    CCPosition getPosition() const;
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

    void stop           () const;
    void attackUnit     (const Unit & target) const;
    void attackMove     (const CCPosition & targetPosition) const;
    void move           (const CCPosition & targetPosition) const;
    void move           (const CCTilePosition & targetTilePosition) const;
    void rightClick     (const Unit & target) const;
    void repair         (const Unit & target) const;
    void build          (const CCUnitType & buildingType, CCTilePosition pos) const;
    void buildTarget    (const CCUnitType & buildingType, const Unit & target) const;
    void train          (const CCUnitType & buildingType) const;
};
