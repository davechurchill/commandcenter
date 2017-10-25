#include "SquadData.h"
#include "CCBot.h"
#include "Util.h"

SquadData::SquadData(CCBot & bot)
    : m_bot(bot)
{

}

void SquadData::onFrame()
{
    updateAllSquads();
    verifySquadUniqueMembership();
    drawSquadInformation();
}

void SquadData::clearSquadData()
{
    // give back workers who were in squads
    for (auto & kv : m_squads)
    {
        Squad & squad = kv.second;
        for (auto & unit : squad.getUnits())
        {
            BOT_ASSERT(unit.isValid(), "null unit");

            if (unit.getType().isWorker())
            {
                m_bot.Workers().finishedWithWorker(unit);
            }
        }
    }

    m_squads.clear();
}

void SquadData::removeSquad(const std::string & squadName)
{
    const auto & squadPtr = m_squads.find(squadName);

    BOT_ASSERT(squadPtr != m_squads.end(), "Trying to clear a squad that didn't exist: %s", squadName.c_str());
    if (squadPtr == m_squads.end())
    {
        return;
    }

    for (auto unit : squadPtr->second.getUnits())
    {
        BOT_ASSERT(unit.isValid(), "null unit");

        if (unit.getType().isWorker())
        {
            m_bot.Workers().finishedWithWorker(unit);
        }
    }

    m_squads.erase(squadName);
}

const std::map<std::string, Squad> & SquadData::getSquads() const
{
    return m_squads;
}

bool SquadData::squadExists(const std::string & squadName)
{
    return m_squads.find(squadName) != m_squads.end();
}

void SquadData::addSquad(const std::string & squadName, const Squad & squad)
{
    m_squads.insert(std::pair<std::string, Squad>(squadName, squad));
}

void SquadData::updateAllSquads()
{
    for (auto & kv : m_squads)
    {
        kv.second.onFrame();
    }
}

void SquadData::drawSquadInformation()
{
    if (!m_bot.Config().DrawSquadInfo)
    {
        return;
    }

    std::stringstream ss;
    ss << "Squad Data\n\n";

    for (auto & kv : m_squads)
    {
        const Squad & squad = kv.second;

        auto & units = squad.getUnits();
        const SquadOrder & order = squad.getSquadOrder();

        ss << squad.getName() << " " << units.size() << " (";
        ss << (int)order.getPosition().x << ", " << (int)order.getPosition().y << ")\n";

        m_bot.Map().drawCircle(order.getPosition(), 5, CCColor(255, 0, 0));
        m_bot.Map().drawText(order.getPosition(), squad.getName(), CCColor(255, 0, 0));

        for (auto & unit : units)
        {
            BOT_ASSERT(unit.isValid(), "null unit");

            m_bot.Map().drawText(unit.getPosition(), squad.getName(), CCColor(0, 255, 0));
        }
    }

    m_bot.Map().drawTextScreen(0.5f, 0.2f, ss.str(), CCColor(255, 0, 0));
}

void SquadData::verifySquadUniqueMembership()
{
    std::vector<Unit> assigned;

    for (const auto & kv : m_squads)
    {
        for (auto & unit : kv.second.getUnits())
        {
            if (std::find(assigned.begin(), assigned.end(), unit) != assigned.end())
            {
                std::cout << "Warning: Unit is in at least two squads: " << unit.getID() << "\n";
            }

            assigned.push_back(unit);
        }
    }
}

bool SquadData::unitIsInSquad(const Unit & unit) const
{
    return getUnitSquad(unit) != nullptr;
}

const Squad * SquadData::getUnitSquad(const Unit & unit) const
{
    for (const auto & kv : m_squads)
    {
        if (kv.second.containsUnit(unit))
        {
            return &kv.second;
        }
    }

    return nullptr;
}

Squad * SquadData::getUnitSquad(const Unit & unit)
{
    for (auto & kv : m_squads)
    {
        if (kv.second.containsUnit(unit))
        {
            return &kv.second;
        }
    }

    return nullptr;
}

void SquadData::assignUnitToSquad(const Unit & unit, Squad & squad)
{
    BOT_ASSERT(canAssignUnitToSquad(unit, squad), "We shouldn't be re-assigning this unit!");

    Squad * previousSquad = getUnitSquad(unit);

    if (previousSquad)
    {
        previousSquad->removeUnit(unit);
    }

    squad.addUnit(unit);
}

bool SquadData::canAssignUnitToSquad(const Unit & unit, const Squad & squad) const
{
    const Squad * unitSquad = getUnitSquad(unit);

    // make sure strictly less than so we don't reassign to the same squad etc
    return !unitSquad || (unitSquad->getPriority() < squad.getPriority());
}

Squad & SquadData::getSquad(const std::string & squadName)
{
    BOT_ASSERT(squadExists(squadName), "Trying to access squad that doesn't exist: %s", squadName.c_str());
    if (!squadExists(squadName))
    {
        int a = 10;
    }

    return m_squads.at(squadName);
}