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
    for (auto & workerTag : getWorkers())
    {
        auto worker = m_bot.GetUnit(workerTag);
        if (worker == nullptr) { continue; }

        // if it's idle
        if (getWorkerJob(workerTag) == WorkerJobs::None)
        {
            setWorkerJob(workerTag, WorkerJobs::Idle);
        }

        // TODO: If it's a gas worker whose refinery has been destroyed, set to minerals
    }

    // remove any worker units which no longer exist in the game
    std::vector<UnitTag> workersDestroyed;
    for (auto & workerTag : getWorkers())
    {
        const sc2::Unit * worker = m_bot.GetUnit(workerTag);

        // TODO: for now skip gas workers because they disappear inside refineries, this is annoying
        if (!worker && (getWorkerJob(workerTag) != WorkerJobs::Gas))
        {
            workersDestroyed.push_back(workerTag);
        }
    }

    for (auto tag : workersDestroyed)
    {
        workerDestroyed(tag);
    }
}

void WorkerData::workerDestroyed(const UnitTag & unit)
{
    clearPreviousJob(unit);
    m_workers.erase(unit);
}

void WorkerData::updateWorker(const UnitTag & unit)
{
    if (m_workers.find(unit) == m_workers.end())
    {
        m_workers.insert(unit);
        m_workerJobMap[unit] = WorkerJobs::None;
    }
}

void WorkerData::setWorkerJob(const UnitTag & unit, int job, UnitTag jobUnitTag)
{
    clearPreviousJob(unit);
    m_workerJobMap[unit] = job;
    m_workerJobCount[job]++;

    if (job == WorkerJobs::Minerals)
    {
        // if we haven't assigned anything to this depot yet, set its worker count to 0
        if (m_depotWorkerCount.find(jobUnitTag) == m_depotWorkerCount.end())
        {
            m_depotWorkerCount[jobUnitTag] = 0;
        }

        // add the depot to our set of depots
        m_depots.insert(jobUnitTag);

        // increase the worker count of this depot
        m_workerDepotMap[unit] = jobUnitTag;
        m_depotWorkerCount[jobUnitTag]++;

        // find the mineral to mine and mine it
        UnitTag mineralToMine = getMineralToMine(unit);
        Micro::SmartRightClick(unit, mineralToMine, m_bot);
    }
    else if (job == WorkerJobs::Gas)
    {
        // if we haven't assigned any workers to this refinery yet set count to 0
        if (m_refineryWorkerCount.find(jobUnitTag) == m_refineryWorkerCount.end())
        {
            m_refineryWorkerCount[jobUnitTag] = 0;
        }

        // increase the count of workers assigned to this refinery
        m_refineryWorkerCount[jobUnitTag] += 1;
        m_workerRefineryMap[unit] = jobUnitTag;

        // right click the refinery to start harvesting
        Micro::SmartRightClick(unit, jobUnitTag, m_bot);
    }
    else if (job == WorkerJobs::Repair)
    {
        Micro::SmartRepair(unit, jobUnitTag, m_bot);
    }
    else if (job == WorkerJobs::Scout)
    {

    }
    else if (job == WorkerJobs::Build)
    {

    }
}

void WorkerData::clearPreviousJob(const UnitTag & unit)
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

int WorkerData::getWorkerJob(const UnitTag & unit) const
{
    auto it = m_workerJobMap.find(unit);

    if (it != m_workerJobMap.end())
    {
        return it->second;
    }

    return WorkerJobs::None;
}

UnitTag WorkerData::getMineralToMine(const UnitTag & unit) const
{
    UnitTag bestMineral = -1;
    double bestDist = 100000;

    for (auto & mineral : m_bot.Observation()->GetUnits())
    {
        if (!Util::IsMineral(mineral)) continue;

        double dist = Util::Dist(mineral.pos, m_bot.GetUnit(unit)->pos);

        if (dist < bestDist)
        {
            bestMineral = mineral.tag;
            bestDist = dist;
        }
    }

    return bestMineral;
}

UnitTag WorkerData::getWorkerDepot(const UnitTag & unit) const
{
    auto it = m_workerDepotMap.find(unit);

    if (it != m_workerDepotMap.end())
    {
        return it->second;
    }

    return -1;
}

int WorkerData::getNumAssignedWorkers(const UnitTag & unit)
{
    if (Util::IsTownHall(*m_bot.GetUnit(unit)))
    {
        auto it = m_depotWorkerCount.find(unit);

        // if there is an entry, return it
        if (it != m_depotWorkerCount.end())
        {
            return it->second;
        }
    }
    else if (Util::IsRefinery(*m_bot.GetUnit(unit)))
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

const char * WorkerData::getJobCode(const UnitTag & unit)
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
    for (auto & depotTag : m_depots)
    {
        auto depot = m_bot.GetUnit(depotTag);

        std::stringstream ss;
        ss << "Workers: " << getNumAssignedWorkers(depot->tag);

        m_bot.Map().drawText(depot->pos, ss.str());
    }
}

const std::set<UnitTag> & WorkerData::getWorkers() const
{
    return m_workers;
}