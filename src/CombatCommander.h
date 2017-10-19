#pragma once

#include "Common.h"
#include "Squad.h"
#include "SquadData.h"

class CCBot;

class CombatCommander
{
    CCBot &         m_bot;

    SquadData       m_squadData;
    std::vector<CCUnit>  m_combatUnits;
    bool            m_initialized;
    bool            m_attackStarted;

    void            updateScoutDefenseSquad();
    void            updateDefenseSquads();
    void            updateAttackSquads();
    void            updateIdleSquad();
    bool            isSquadUpdateFrame();

    CCUnit findClosestDefender(const Squad & defenseSquad, const CCPosition & pos);
    CCUnit findClosestWorkerTo(std::vector<CCUnit> & unitsToAssign, const CCPosition & target);

    CCPosition    getMainAttackLocation();

    void            updateDefenseSquadUnits(Squad & defenseSquad, const size_t & flyingDefendersNeeded, const size_t & groundDefendersNeeded);
    bool            shouldWeStartAttacking();

public:

    CombatCommander(CCBot & bot);


    void onStart();
    void onFrame(const std::vector<CCUnit> & combatUnits);

    void drawSquadInformation();
};

