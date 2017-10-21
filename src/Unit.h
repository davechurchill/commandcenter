#pragma once

#include "Common.h"

class CCBot;

class Unit
{
    CCBot &     m_bot;
    CCUnit      m_unit;
    CCUnitID    m_unitID;

public:

    Unit(CCUnit unit, CCBot & bot);

    CCUnit getUnitPtr() const;

    const CCPosition & getPosition() const;
    CCHealth getHitPoints() const;
    CCHealth getShields() const;
    CCHealth getEnergy() const;
    CCPlayer getPlayer() const;
    CCUnitID getID() const;
    int getWeaponCooldown() const;
    bool isCompleted() const;
    bool isCloaked() const;
    bool isFlying() const;
    bool isAlive() const;
    bool isPowered() const;
    bool isIdle() const;
    bool isBurrowed() const;
    bool isValid() const;

    void stop           ();
    void attackUnit     (const Unit & target);
    void attackMove     (const CCPosition & targetPosition);
    void move           (const CCPosition & targetPosition);
    void move           (const CCTilePosition & targetTilePosition);
    void rightClick     (const Unit & target);
    void repair         (const Unit & target);
    void build          (const CCUnitType & buildingType, CCTilePosition pos);
    void buildTarget    (const CCUnitType & buildingType, const Unit & target);
    void train          (const CCUnitType & buildingType);
};
