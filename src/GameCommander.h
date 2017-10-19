#pragma once

#include "Common.h"
#include "Timer.hpp"
#include "ProductionManager.h"
#include "ScoutManager.h"
#include "CombatCommander.h"

class CCBot;

class GameCommander
{
    CCBot &                 m_bot;
    Timer                   m_timer;

    ProductionManager       m_productionManager;
    ScoutManager            m_scoutManager;
    CombatCommander         m_combatCommander;

    std::vector<CCUnit>    m_validUnits;
    std::vector<CCUnit>    m_combatUnits;
    std::vector<CCUnit>    m_scoutUnits;

    bool                    m_initialScoutSet;

    void assignUnit(CCUnit unit, std::vector<CCUnit> & units);
    bool isAssigned(CCUnit unit) const;

public:

    GameCommander(CCBot & bot);

    void onStart();
    void onFrame();

    void handleUnitAssignments();
    void setValidUnits();
    void setScoutUnits();
    void setCombatUnits();

    void drawDebugInterface();
    void drawGameInformation(int x, int y);

    bool shouldSendInitialScout();

    void onUnitCreate(CCUnit unit);
    void onUnitDestroy(CCUnit unit);
};
