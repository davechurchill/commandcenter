#include "WorkerManager.h"
#include "Micro.h"
#include "CCBot.h"
#include "Util.h"
#include "Building.h"

WorkerManager::WorkerManager(CCBot & bot)
    : m_bot         (bot)
    , m_workerData  (bot)
{
    m_previousClosestWorker = -1;
}

void WorkerManager::onStart()
{

}

void WorkerManager::onFrame()
{
    m_workerData.updateAllWorkerData();
    handleGasWorkers();
    handleIdleWorkers();

    drawResourceDebugInfo();
    drawWorkerInformation();

    m_workerData.drawDepotDebugInfo();

    handleRepairWorkers();
}

void WorkerManager::setRepairWorker(const sc2::Unit & worker, const sc2::Unit & unitToRepair)
{
    m_workerData.setWorkerJob(worker, WorkerJobs::Repair, unitToRepair);
}

void WorkerManager::stopRepairing(const sc2::Unit & worker)
{
    m_workerData.setWorkerJob(worker, WorkerJobs::Idle);
}

void WorkerManager::handleGasWorkers()
{
    // for each unit we have
    for (auto & unit : m_bot.UnitInfo().getUnits(Players::Self))
    {
        // if that unit is a refinery
        if (Util::IsRefinery(unit) && Util::IsCompleted(unit))
        {
            // get the number of workers currently assigned to it
            int numAssigned = m_workerData.getNumAssignedWorkers(unit);

            // if it's less than we want it to be, fill 'er up
            for (int i=0; i<(3-numAssigned); ++i)
            {
                UnitTag gasWorker = getGasWorker(unit);
                if (gasWorker)
                {
                    m_workerData.setWorkerJob(gasWorker, WorkerJobs::Gas, unit.tag);
                }
            }
        }
    }
}

void WorkerManager::handleIdleWorkers()
{
    // for each of our workers
    for (auto & workerTag : m_workerData.getWorkers())
    {
        auto worker = m_bot.GetUnit(workerTag);
        if (!worker) { continue; }

        // if it's a scout, don't handle it here
        if (m_workerData.getWorkerJob(workerTag) == WorkerJobs::Scout)
        {
            continue;
        }

        // if it is idle
        if (Util::IsIdle(*worker) || m_workerData.getWorkerJob(workerTag) == WorkerJobs::Idle)
        {
            const sc2::Unit * workerUnit = m_bot.GetUnit(workerTag);

            // send it to the nearest mineral patch
            if (workerUnit)
            {
                setMineralWorker(*workerUnit);
            }
        }
    }
}

void WorkerManager::handleRepairWorkers()
{
    // TODO
}

UnitTag WorkerManager::getClosestMineralWorkerTo(const sc2::Point2D & pos) const
{
    UnitTag closestMineralWorker = 0;
    double closestDist = std::numeric_limits<double>::max();

    // for each of our workers
    for (auto & workerTag : m_workerData.getWorkers())
    {
        if (!m_bot.GetUnit(workerTag)) { continue; }

        // if it is a mineral worker
        if (m_workerData.getWorkerJob(workerTag) == WorkerJobs::Minerals)
        {
            double dist = Util::DistSq(m_bot.GetUnit(workerTag)->pos, pos);

            if (!closestMineralWorker || dist < closestDist)
            {
                closestMineralWorker = workerTag;
                dist = closestDist;
            }
        }
    }

    return closestMineralWorker;
}


// set a worker to mine minerals
void WorkerManager::setMineralWorker(const sc2::Unit & unit)
{
    // check if there is a mineral available to send the worker to
    UnitTag depot = getClosestDepot(unit);

    // if there is a valid mineral
    if (depot)
    {
        // update m_workerData with the new job
        m_workerData.setWorkerJob(unit, WorkerJobs::Minerals, depot);
    }
}

UnitTag WorkerManager::getClosestDepot(const sc2::Unit & worker) const
{
    UnitTag closestDepot = 0;
    double closestDistance = std::numeric_limits<double>::max();

    for (auto & unit : m_bot.UnitInfo().getUnits(Players::Self))
    {
        if (!m_bot.GetUnit(unit)) { continue; }

        if (Util::IsTownHall(unit) && Util::IsCompleted(unit))
        {
            double distance = Util::DistSq(unit.pos, worker.pos);
            if (!closestDepot || distance < closestDistance)
            {
                closestDepot = unit;
                closestDistance = distance;
            }
        }
    }

    return closestDepot;
}


// other managers that need workers call this when they're done with a unit
void WorkerManager::finishedWithWorker(const UnitTag & tag)
{
    if (m_workerData.getWorkerJob(tag) != WorkerJobs::Scout)
    {
        m_workerData.setWorkerJob(tag, WorkerJobs::Idle);
    }
}

UnitTag WorkerManager::getGasWorker(const sc2::Unit & refinery) const
{
    return getClosestMineralWorkerTo(refinery.pos);
}

void WorkerManager::setBuildingWorker(const sc2::Unit & worker, Building & b)
{
    m_workerData.setWorkerJob(worker, WorkerJobs::Build, b.type);
}

// gets a builder for BuildingManager to use
// if setJobAsBuilder is true (default), it will be flagged as a builder unit
// set 'setJobAsBuilder' to false if we just want to see which worker will build a building
UnitTag WorkerManager::getBuilder(Building & b, bool setJobAsBuilder) const
{
    UnitTag builderWorker = getClosestMineralWorkerTo(b.finalPosition);

    // if the worker exists (one may not have been found in rare cases)
    if (builderWorker && setJobAsBuilder)
    {
        m_workerData.setWorkerJob(builderWorker, WorkerJobs::Build, b.type);
    }

    return builderWorker;
}

// sets a worker as a scout
void WorkerManager::setScoutWorker(const UnitTag & workerTag)
{
    m_workerData.setWorkerJob(workerTag, WorkerJobs::Scout);
}

void WorkerManager::setCombatWorker(const UnitTag & workerTag)
{
    m_workerData.setWorkerJob(workerTag, WorkerJobs::Combat);
}

void WorkerManager::drawResourceDebugInfo()
{
    if (!m_bot.Config().DrawResourceInfo)
    {
        return;
    }

    for (auto & workerTag : m_workerData.getWorkers())
    {
        if (!m_bot.GetUnit(workerTag)) { continue; }

        m_bot.Map().drawText(m_bot.GetUnit(workerTag)->pos, m_workerData.getJobCode(workerTag));

        auto depot = m_bot.GetUnit(m_workerData.getWorkerDepot(workerTag));
        if (depot)
        {
            m_bot.Map().drawLine(m_bot.GetUnit(workerTag)->pos, depot->pos);
        }
    }
}

void WorkerManager::drawWorkerInformation()
{
    if (!m_bot.Config().DrawWorkerInfo)
    {
        return;
    }

    std::stringstream ss;
    ss << "Workers: " << m_workerData.getWorkers().size() << "\n";

    int yspace = 0;

    for (auto & workerTag : m_workerData.getWorkers())
    {
        ss << m_workerData.getJobCode(workerTag) << " " << workerTag << "\n";
    }

    m_bot.Map().drawTextScreen(sc2::Point2D(0.75f, 0.2f), ss.str());
}

bool WorkerManager::isFree(const sc2::Unit & worker) const
{
    return m_workerData.getWorkerJob(worker) == WorkerJobs::Minerals || m_workerData.getWorkerJob(worker) == WorkerJobs::Idle;
}

bool WorkerManager::isWorkerScout(const sc2::Unit & worker) const
{
    return (m_workerData.getWorkerJob(worker) == WorkerJobs::Scout);
}

bool WorkerManager::isBuilder(const sc2::Unit & worker) const
{
    return (m_workerData.getWorkerJob(worker) == WorkerJobs::Build);
}

int WorkerManager::getNumMineralWorkers()
{
    return m_workerData.getWorkerJobCount(WorkerJobs::Minerals);
}

int WorkerManager::getNumGasWorkers()
{
    return m_workerData.getWorkerJobCount(WorkerJobs::Gas);

}
