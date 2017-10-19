#pragma once

#include "Common.h"
#include "MeleeManager.h"
#include "RangedManager.h"
#include "SquadOrder.h"

class CCBot;

class Squad
{
    CCBot &             m_bot;

    std::string         m_name;
    std::set<CCUnit> m_units;
    std::string         m_regroupStatus;
    int                 m_lastRetreatSwitch;
    bool                m_lastRetreatSwitchVal;
    size_t              m_priority;

    SquadOrder          m_order;
    MeleeManager        m_meleeManager;
    RangedManager       m_rangedManager;

    std::map<CCUnit, bool> m_nearEnemy;

    CCUnit unitClosestToEnemy() const;

    void updateUnits();
    void addUnitsToMicroManagers();
    void setNearEnemyUnits();
    void setAllUnits();

    bool isUnitNearEnemy(CCUnit unit) const;
    bool needsToRegroup() const;
    int  squadUnitsNear(const sc2::Point2D & pos) const;

public:

    Squad(const std::string & name, const SquadOrder & order, size_t priority, CCBot & bot);
    Squad(CCBot & bot);

    void onFrame();
    void setSquadOrder(const SquadOrder & so);
    void addUnit(CCUnit unit);
    void removeUnit(CCUnit unit);
    void clear();

    bool containsUnit(CCUnit unit) const;
    bool isEmpty() const;
    size_t getPriority() const;
    void setPriority(const size_t & priority);
    const std::string & getName() const;

    sc2::Point2D calcCenter() const;
    sc2::Point2D calcRegroupPosition() const;

    const std::set<CCUnit> & getUnits() const;
    const SquadOrder & getSquadOrder() const;
};
