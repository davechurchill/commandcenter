#pragma once

#include "Common.h"

class CCBot;

class UnitType
{
    mutable CCBot * m_bot;
    
#ifdef SC2API
    sc2::UnitTypeID m_type;
#else
    BWAPI::UnitType m_type;
#endif

public:

    UnitType();

#ifdef SC2API
    UnitType(sc2::UnitTypeID type, CCBot & bot);
    sc2::UnitTypeID getAPIUnitType() const;
#else
    UnitType(const BWAPI::Unit type, CCBot & bot);
    BWAPI::UnitType getAPIUnitType() const;
#endif

    bool operator < (const UnitType & rhs) const;
    bool operator == (const UnitType & rhs) const;

    CCRace getRace() const;
    
    bool isBuilding() const;
    bool isCombatUnit() const;
    bool isSupplyProvider() const;
    bool isResourceDepot() const;
    bool isRefinery() const;
    bool isDetector() const;
    bool isGeyser() const;
    bool isMineral() const;
    bool isWorker() const;
    bool canAttack() const;
    bool canMove() const;
    bool isAddon() const;
    float getAttackRange() const;
    int tileWidth() const;
    int tileHeight() const;
    int supplyProvided() const;
    int supplyRequired() const;
};
