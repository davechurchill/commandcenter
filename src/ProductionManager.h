#pragma once
#include "sc2api/sc2_api.h"
#include "Common.h"
#include "BuildOrder.h"
#include "BuildingManager.h"
#include "BuildOrderQueue.h"

class CCBot;

class ProductionManager
{
    CCBot &       m_bot;

    BuildingManager m_buildingManager;
    BuildOrderQueue m_queue;

    CCUnit getClosestUnitToPosition(const std::vector<CCUnit> & units, CCPosition closestTo);
    bool    meetsReservedResources(const BuildType & type);
    bool    canMakeNow(CCUnit producer, const BuildType & type);
    bool    detectBuildOrderDeadlock();
    void    setBuildOrder(const BuildOrder & buildOrder);
    void    create(CCUnit producer, BuildOrderItem & item);
    void    manageBuildOrderQueue();
    int     getFreeMinerals();
    int     getFreeGas();

public:

    ProductionManager(CCBot & bot);

    void    onStart();
    void    onFrame();
    void    onUnitDestroy(CCUnit unit);
    void    drawProductionInformation();

    CCUnit getProducer(const BuildType & type, CCPosition closestTo = CCPosition(0, 0));
};
