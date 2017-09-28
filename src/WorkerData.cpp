#include "WorkerData.h"
#include "Micro.h"
#include "Util.h"
#include "CCBot.h"
#include <iostream>
#include <sstream>

WorkerData::WorkerData(CCBot & bot)
    : m_bot(bot)
{
    for (int i=0; i < WorkerJobs::Num; ++i)
    {
        m_workerJobCount[i] = 0;
    }
}

void WorkerData::updateAllWorkerData()
{
    // check all our units and add new workers if we find them
    for (auto & unit : m_bot.UnitInfo().getUnits(Players::Self))
    {
        if (Util::IsWorker(unit))
        {
            updateWorker(unit);
        }
    }

    // for each of our Workers
    for (auto worker : getWorkers())
    {
        // if it's idle
        if (getWorkerJob(worker) == WorkerJobs::None)
        {
            setWorkerJob(worker, WorkerJobs::Idle);
        }

        // TODO: If it's a gas worker whose refinery has been destroyed, set to minerals
    }

    // remove any worker units which no longer exist in the game
    std::vector<const sc2::Unit *> workersDestroyed;
    for (auto worker : getWorkers())
    {
        // TODO: for now skip gas workers because they disappear inside refineries, this is annoying
        if (!worker && (getWorkerJob(worker) != WorkerJobs::Gas))
        {
            workersDestroyed.push_back(worker);
        }
    }

    for (auto worker : workersDestroyed)
    {
        workerDestroyed(worker);
    }
}

void WorkerData::workerDestroyed(const sc2::Unit * unit)
{
    clearPreviousJob(unit);
    m_workers.erase(unit);
}

void WorkerData::updateWorker(const sc2::Unit * unit)
{
    if (m_workers.find(unit) == m_workers.end())
    {
        m_workers.insert(unit);
        m_workerJobMap[unit] = WorkerJobs::None;
    }
}

void WorkerData::setWorkerJob(const sc2::Unit * unit, int job, const sc2::Unit * jobUnit)
{
    clearPreviousJob(unit);
    m_workerJobMap[unit] = job;
    m_workerJobCount[job]++;

    if (job == WorkerJobs::Minerals)
    {
        // if we haven't assigned anything to this depot yet, set its worker count to 0
        if (m_depotWorkerCount.find(jobUnit) == m_depotWorkerCount.end())
        {
            m_depotWorkerCount[jobUnit] = 0;
        }

        // add the depot to our set of depots
        m_depots.insert(jobUnit);

        // increase the worker count of this depot
        m_workerDepotMap[unit] = jobUnit;
        m_depotWorkerCount[jobUnit]++;

        // find the mineral to mine and mine it
        const sc2::Unit * mineralToMine = getMineralToMine(unit);
        
        Micro::SmartRightClick(unit, mineralToMine, m_bot);
    }
    else if (job == WorkerJobs::Gas)
    {
        // if we haven't assigned any workers to this refinery yet set count to 0
        if (m_refineryWorkerCount.find(jobUnit) == m_refineryWorkerCount.end())
        {
            m_refineryWorkerCount[jobUnit] = 0;
        }

        // increase the count of workers assigned to this refinery
        m_refineryWorkerCount[jobUnit] += 1;
        m_workerRefineryMap[unit] = jobUnit;

        // right click the refinery to start harvesting
        Micro::SmartRightClick(unit, jobUnit, m_bot);
    }
    else if (job == WorkerJobs::Repair)
    {
        Micro::SmartRepair(unit, jobUnit, m_bot);
    }
    else if (job == WorkerJobs::Scout)
    {

    }
    else if (job == WorkerJobs::Build)
    {

    }
}

void WorkerData::clearPreviousJob(const sc2::Unit * unit)
{
    const int previousJob = getWorkerJob(unit);
    m_workerJobCount[previousJob]--;

    if (previousJob == WorkerJobs::Minerals)
    {
        // remove one worker from the count of the depot this worker was assigned to
        m_depotWorkerCount[m_workerDepotMap[unit]]--;
        m_workerDepotMap.erase(unit);
    }
    else if (previousJob == WorkerJobs::Gas)
    {
        m_refineryWorkerCount[m_workerRefineryMap[unit]]--;
        m_workerRefineryMap.erase(unit);
    }
    else if (previousJob == WorkerJobs::Build)
    {

    }
    else if (previousJob == WorkerJobs::Repair)
    {

    }
    else if (previousJob == WorkerJobs::Move)
    {

    }

    m_workerJobMap.erase(unit);
}

size_t WorkerData::getNumWorkers() const
{
    return m_workers.size();
}

int WorkerData::getWorkerJobCount(int job) const
{
    return m_workerJobCount.at(job);
}

int WorkerData::getWorkerJob(const sc2::Unit * unit) const
{
    auto it = m_workerJobMap.find(unit);

    if (it != m_workerJobMap.end())
    {
        return it->second;
    }

    return WorkerJobs::None;
}

const sc2::Unit * WorkerData::getMineralToMine(const sc2::Unit * unit) const
{
    const sc2::Unit * bestMineral = nullptr;
    double bestDist = 100000;

    for (auto mineral : m_bot.Observation()->GetUnits())
    {
        if (!Util::IsMineral(mineral)) continue;

        double dist = Util::Dist(mineral->pos, unit->pos);

        if (dist < bestDist)
        {
            bestMineral = mineral;
            bestDist = dist;
        }
    }

    return bestMineral;
}

const sc2::Unit * WorkerData::getWorkerDepot(const sc2::Unit * unit) const
{
    auto it = m_workerDepotMap.find(unit);

    if (it != m_workerDepotMap.end())
    {
        return it->second;
    }

    return nullptr;
}

int WorkerData::getNumAssignedWorkers(const sc2::Unit * unit)
{
    if (Util::IsTownHall(unit))
    {
        auto it = m_depotWorkerCount.find(unit);

        // if there is an entry, return it
        if (it != m_depotWorkerCount.end())
        {
            return it->second;
        }
    }
    else if (Util::IsRefinery(unit))
    {
        auto it = m_refineryWorkerCount.find(unit);

        // if there is an entry, return it
        if (it != m_refineryWorkerCount.end())
        {
            return it->second;
        }
        // otherwise, we are only calling this on completed refineries, so set it
        else
        {
            m_refineryWorkerCount[unit] = 0;
        }
    }

    // when all else fails, return 0
    return 0;
}

const char * WorkerData::getJobCode(const sc2::Unit * unit)
{
    const int j = getWorkerJob(unit);

    if (j == WorkerJobs::Build)     return "B";
    if (j == WorkerJobs::Combat)    return "C";
    if (j == WorkerJobs::None)      return "N";
    if (j == WorkerJobs::Gas)       return "G";
    if (j == WorkerJobs::Idle)      return "I";
    if (j == WorkerJobs::Minerals)  return "M";
    if (j == WorkerJobs::Repair)    return "R";
    if (j == WorkerJobs::Move)      return "O";
    if (j == WorkerJobs::Scout)     return "S";
    return "X";
}

void WorkerData::drawDepotDebugInfo()
{
    for (auto depot: m_depots)
    {
        std::stringstream ss;
        ss << "Workers: " << getNumAssignedWorkers(depot);

        m_bot.Map().drawText(depot->pos, ss.str());
    }
}

const std::set<const sc2::Unit *> & WorkerData::getWorkers() const
{
    return m_workers;
}