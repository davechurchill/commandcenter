#pragma once

#include "Common.h"

class CCBot;

class ScoutManager
{
    CCBot &   m_bot;

    CCUnit m_scoutUnit;
    std::string     m_scoutStatus;
    int             m_numScouts;
    bool            m_scoutUnderAttack;
    float           m_previousScoutHP;

    bool            enemyWorkerInRadiusOf(const CCPosition & pos) const;
    CCPosition    getFleePosition() const;
    CCUnit closestEnemyWorkerTo(const CCPosition & pos) const;
    void            moveScouts();
    void            drawScoutInformation();


public:

    ScoutManager(CCBot & bot);

    void onStart();
    void onFrame();
    void setWorkerScout(CCUnit unit);
};