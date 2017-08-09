#pragma once

#include "WorkerData.h"

class Building;
class CCBot;

class WorkerManager
{
    CCBot & m_bot;

    mutable WorkerData  m_workerData;
    UnitTag     m_previousClosestWorker;

    void        setMineralWorker(const sc2::Unit & unit);
    
    void        handleIdleWorkers();
    void        handleGasWorkers();
    void        handleRepairWorkers();

public:

    WorkerManager(CCBot & bot);

    void        onStart();
    void        onFrame();

    void        finishedWithWorker(const UnitTag & tag);
    void        drawResourceDebugInfo();
    void        drawWorkerInformation();
    void        setScoutWorker(const UnitTag & worker);
    void        setCombatWorker(const UnitTag & worker);
    void        setBuildingWorker(const sc2::Unit & worker, Building & b);
    void        setRepairWorker(const sc2::Unit & worker,const sc2::Unit & unitToRepair);
    void        stopRepairing(const sc2::Unit & worker);

    int         getNumMineralWorkers();
    int         getNumGasWorkers();
    bool        isWorkerScout(const sc2::Unit & worker) const;
    bool        isFree(const sc2::Unit & worker) const;
    bool        isBuilder(const sc2::Unit & worker) const;

    UnitTag     getBuilder(Building & b,bool setJobAsBuilder = true) const;
    UnitTag     getClosestDepot(const sc2::Unit & worker) const;
    UnitTag     getGasWorker(const sc2::Unit & refinery) const;
    UnitTag     getClosestMineralWorkerTo(const sc2::Point2D & pos) const;
};

