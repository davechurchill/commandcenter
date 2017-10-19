#pragma once
#include "Common.h"

class CCBot;

namespace WorkerJobs
{
    enum { Minerals, Gas, Build, Combat, Idle, Repair, Move, Scout, None, Num };
}

class WorkerData
{
    CCBot & m_bot;

    std::set<CCUnit>         m_workers;
    std::set<CCUnit>         m_depots;
    std::map<int, int>                  m_workerJobCount;
    std::map<CCUnit, int>    m_workerJobMap;
    std::map<CCUnit, int>    m_refineryWorkerCount;
    std::map<CCUnit, int>    m_depotWorkerCount;
    std::map<CCUnit, CCUnit>  m_workerRefineryMap;
    std::map<CCUnit, CCUnit>  m_workerDepotMap;

    void clearPreviousJob(CCUnit unit);

public:

    WorkerData(CCBot & bot);

    void    workerDestroyed(CCUnit unit);
    void    updateAllWorkerData();
    void    updateWorker(CCUnit unit);
    void    setWorkerJob(CCUnit unit, int job, CCUnit jobUnit = 0);
    void    drawDepotDebugInfo();
    size_t  getNumWorkers() const;
    int     getWorkerJobCount(int job) const;
    int     getNumAssignedWorkers(CCUnit unit);
    int     getWorkerJob(CCUnit unit) const;
    CCUnit getMineralToMine(CCUnit unit) const;
    CCUnit getWorkerDepot(CCUnit unit) const;
    const char * getJobCode(CCUnit unit);
    const std::set<CCUnit> & getWorkers() const;
};