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

    std::set<const sc2::Unit *>         m_workers;
    std::set<const sc2::Unit *>         m_depots;
    std::map<int, int>                  m_workerJobCount;
    std::map<const sc2::Unit *, int>    m_workerJobMap;
    std::map<const sc2::Unit *, int>    m_refineryWorkerCount;
    std::map<const sc2::Unit *, int>    m_depotWorkerCount;
    std::map<const sc2::Unit *, const sc2::Unit *>  m_workerRefineryMap;
    std::map<const sc2::Unit *, const sc2::Unit *>  m_workerDepotMap;

    void clearPreviousJob(const sc2::Unit * unit);

public:

    WorkerData(CCBot & bot);

    void    workerDestroyed(const sc2::Unit * unit);
    void    updateAllWorkerData();
    void    updateWorker(const sc2::Unit * unit);
    void    setWorkerJob(const sc2::Unit * unit, int job, const sc2::Unit * jobUnit = 0);
    void    drawDepotDebugInfo();
    size_t  getNumWorkers() const;
    int     getWorkerJobCount(int job) const;
    int     getNumAssignedWorkers(const sc2::Unit * unit);
    int     getWorkerJob(const sc2::Unit * unit) const;
    const sc2::Unit * getMineralToMine(const sc2::Unit * unit) const;
    const sc2::Unit * getWorkerDepot(const sc2::Unit * unit) const;
    const char * getJobCode(const sc2::Unit * unit);
    const std::set<const sc2::Unit *> & getWorkers() const;
};