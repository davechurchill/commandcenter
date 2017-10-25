#pragma once

#include "Common.h"
#include "Unit.h"

class CCBot;

class ScoutManager
{
    CCBot &   m_bot;

    Unit m_scoutUnit;
    std::string     m_scoutStatus;
    int             m_numScouts;
    bool            m_scoutUnderAttack;
    CCHealth        m_previousScoutHP;

    bool            enemyWorkerInRadiusOf(const CCPosition & pos) const;
    CCPosition      getFleePosition() const;
    Unit            closestEnemyWorkerTo(const CCPosition & pos) const;
    void            moveScouts();
    void            drawScoutInformation();


public:

    ScoutManager(CCBot & bot);

    void onStart();
    void onFrame();
    void setWorkerScout(const Unit & unit);
};