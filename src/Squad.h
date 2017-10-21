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
    std::set<Unit> m_units;
    std::string         m_regroupStatus;
    int                 m_lastRetreatSwitch;
    bool                m_lastRetreatSwitchVal;
    size_t              m_priority;

    SquadOrder          m_order;
    MeleeManager        m_meleeManager;
    RangedManager       m_rangedManager;

    std::map<Unit, bool> m_nearEnemy;

    Unit unitClosestToEnemy() const;

    void updateUnits();
    void addUnitsToMicroManagers();
    void setNearEnemyUnits();
    void setAllUnits();

    bool isUnitNearEnemy(const Unit & unit) const;
    bool needsToRegroup() const;
    int  squadUnitsNear(const CCPosition & pos) const;

public:

    Squad(const std::string & name, const SquadOrder & order, size_t priority, CCBot & bot);
    Squad(CCBot & bot);

    void onFrame();
    void setSquadOrder(const SquadOrder & so);
    void addUnit(const Unit & unit);
    void removeUnit(const Unit & unit);
    void clear();

    bool containsUnit(const Unit & unit) const;
    bool isEmpty() const;
    size_t getPriority() const;
    void setPriority(const size_t & priority);
    const std::string & getName() const;

    CCPosition calcCenter() const;
    CCPosition calcRegroupPosition() const;

    const std::set<Unit> & getUnits() const;
    const SquadOrder & getSquadOrder() const;
};
