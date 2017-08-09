#pragma once

#include "Common.h"
#include "Squad.h"

class CCBot;

class SquadData
{
    CCBot & m_bot;
    std::map<std::string, Squad> m_squads;

    void    updateAllSquads();
    void    verifySquadUniqueMembership();

public:

    SquadData(CCBot & bot);

    void            onFrame();
    void            clearSquadData();

    bool            canAssignUnitToSquad(const UnitTag & unit, const Squad & squad) const;
    void            assignUnitToSquad(const UnitTag & unit, Squad & squad);
    void            addSquad(const std::string & squadName, const Squad & squad);
    void            removeSquad(const std::string & squadName);
    void            drawSquadInformation();


    bool            squadExists(const std::string & squadName);
    bool            unitIsInSquad(const UnitTag & unit) const;
    const Squad *   getUnitSquad(const UnitTag & unit) const;
    Squad *         getUnitSquad(const UnitTag & unit);

    Squad &         getSquad(const std::string & squadName);
    const std::map<std::string, Squad> & getSquads() const;
};
