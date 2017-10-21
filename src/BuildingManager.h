#pragma once

#include "Common.h"
#include "BuildingPlacer.h"

class CCBot;

class BuildingManager
{
    CCBot &   m_bot;

    BuildingPlacer  m_buildingPlacer;
    std::vector<Building> m_buildings;

    bool            m_debugMode;
    int             m_reservedMinerals;				// minerals reserved for planned buildings
    int             m_reservedGas;					// gas reserved for planned buildings

    bool            isBuildingPositionExplored(const Building & b) const;
    void            removeBuildings(const std::vector<Building> & toRemove);

    void            validateWorkersAndBuildings();		    // STEP 1
    void            assignWorkersToUnassignedBuildings();	// STEP 2
    void            constructAssignedBuildings();			// STEP 3
    void            checkForStartedConstruction();			// STEP 4
    void            checkForDeadTerranBuilders();			// STEP 5
    void            checkForCompletedBuildings();			// STEP 6

    char            getBuildingWorkerCode(const Building & b) const;

public:

    BuildingManager(CCBot & bot);

    void                onStart();
    void                onFrame();
    void                addBuildingTask(const UnitType & type, const CCTilePosition & desiredPosition);
    void                drawBuildingInformation();
    CCTilePosition      getBuildingLocation(const Building & b);

    int                 getReservedMinerals();
    int                 getReservedGas();

    bool                isBeingBuilt(UnitType type);

    std::vector<UnitType> buildingsQueued() const;
};
