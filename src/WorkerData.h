#pragma once
#include "Common.h"
#include "Unit.h"

class CCBot;

namespace WorkerJobs
{
    enum { Minerals, Gas, Build, Combat, Idle, Repair, Move, Scout, None, Num };
}

class WorkerData
{
    CCBot & m_bot;

    std::set<Unit>          m_workers;
    std::set<Unit>          m_depots;
    std::map<int, int>      m_workerJobCount;
    std::map<Unit, int>     m_workerJobMap;
    std::map<Unit, int>     m_refineryWorkerCount;
    std::map<Unit, int>     m_depotWorkerCount;
    std::map<Unit, Unit>    m_workerRefineryMap;
    std::map<Unit, Unit>    m_workerDepotMap;

    void clearPreviousJob(const Unit & unit);

public:

    WorkerData(CCBot & bot);

    void    workerDestroyed(const Unit & unit);
    void    updateAllWorkerData();
    void    updateWorker(const Unit & unit);
    void    setWorkerJob(const Unit & unit, int job, Unit jobUnit = Unit());
    void    drawDepotDebugInfo();
    size_t  getNumWorkers() const;
    int     getWorkerJobCount(int job) const;
    int     getNumAssignedWorkers(const Unit & unit);
    int     getWorkerJob(const Unit & unit) const;
    Unit    getMineralToMine(const Unit & unit) const;
    Unit    getWorkerDepot(const Unit & unit) const;
    const char * getJobCode(const Unit & unit);
    const std::set<Unit> & getWorkers() const;
};