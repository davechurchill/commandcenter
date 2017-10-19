#pragma once

#include "WorkerData.h"

class Building;
class CCBot;

class WorkerManager
{
    CCBot & m_bot;

    mutable WorkerData  m_workerData;
    CCUnit   m_previousClosestWorker;

    void        setMineralWorker(CCUnit unit);
    
    void        handleIdleWorkers();
    void        handleGasWorkers();
    void        handleRepairWorkers();

public:

    WorkerManager(CCBot & bot);

    void        onStart();
    void        onFrame();

    void        finishedWithWorker(CCUnit unit);
    void        drawResourceDebugInfo();
    void        drawWorkerInformation();
    void        setScoutWorker(CCUnit worker);
    void        setCombatWorker(CCUnit worker);
    void        setBuildingWorker(CCUnit worker, Building & b);
    void        setRepairWorker(CCUnit worker,CCUnit unitToRepair);
    void        stopRepairing(CCUnit worker);

    int         getNumMineralWorkers();
    int         getNumGasWorkers();
    bool        isWorkerScout(CCUnit worker) const;
    bool        isFree(CCUnit worker) const;
    bool        isBuilder(CCUnit worker) const;

    CCUnit getBuilder(Building & b,bool setJobAsBuilder = true) const;
    CCUnit getClosestDepot(CCUnit worker) const;
    CCUnit getGasWorker(CCUnit refinery) const;
    CCUnit getClosestMineralWorkerTo(const CCPosition & pos) const;
};

