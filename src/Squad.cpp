#include "Squad.h"
#include "CCBot.h"
#include "Util.h"

Squad::Squad(CCBot & bot)
    : m_bot(bot)
    , m_lastRetreatSwitch(0)
    , m_lastRetreatSwitchVal(false)
    , m_priority(0)
    , m_name("Default")
    , m_meleeManager(bot)
    , m_rangedManager(bot)
{

}

Squad::Squad(const std::string & name, const SquadOrder & order, size_t priority, CCBot & bot)
    : m_bot(bot)
    , m_name(name)
    , m_order(order)
    , m_lastRetreatSwitch(0)
    , m_lastRetreatSwitchVal(false)
    , m_priority(priority)
    , m_meleeManager(bot)
    , m_rangedManager(bot)
{
}

void Squad::onFrame()
{
    // update all necessary unit information within this squad
    updateUnits();

    // determine whether or not we should regroup
    bool needToRegroup = needsToRegroup();
    
    // if we do need to regroup, do it
    if (needToRegroup)
    {
        sc2::Point2D regroupPosition = calcRegroupPosition();

        m_bot.Map().drawSphere(regroupPosition, 3, sc2::Colors::Purple);

        m_meleeManager.regroup(regroupPosition);
        m_rangedManager.regroup(regroupPosition);
    }
    else // otherwise, execute micro
    {
        m_meleeManager.execute(m_order);
        m_rangedManager.execute(m_order);

        //_detectorManager.setUnitClosestToEnemy(unitClosestToEnemy());
        //_detectorManager.execute(_order);
    }
}

bool Squad::isEmpty() const
{
    return m_units.empty();
}

size_t Squad::getPriority() const
{
    return m_priority;
}

void Squad::setPriority(const size_t & priority)
{
    m_priority = priority;
}

void Squad::updateUnits()
{
    setAllUnits();
    setNearEnemyUnits();
    addUnitsToMicroManagers();
}

void Squad::setAllUnits()
{
    // clean up the _units vector just in case one of them died
    std::set<UnitTag> goodUnits;
    for (auto & unitTag : m_units)
    {
        const sc2::Unit * unit = m_bot.GetUnit(unitTag);
        if (!unit) { continue; }
        if (unit->build_progress < 1.0f) { continue; }
        if (unit->health <= 0) { continue; }
        
        goodUnits.insert(unitTag);
    }

    m_units = goodUnits;
}

void Squad::setNearEnemyUnits()
{
    m_nearEnemy.clear();
    for (auto & unitTag : m_units)
    {
        m_nearEnemy[unitTag] = isUnitNearEnemy(unitTag);

        sc2::Color color = m_nearEnemy[unitTag] ? m_bot.Config().ColorUnitNearEnemy : m_bot.Config().ColorUnitNotNearEnemy;
        //m_bot.Map().drawSphereAroundUnit(unitTag, color);
    }
}

void Squad::addUnitsToMicroManagers()
{
    std::vector<UnitTag> meleeUnits;
    std::vector<UnitTag> rangedUnits;
    std::vector<UnitTag> detectorUnits;
    std::vector<UnitTag> transportUnits;
    std::vector<UnitTag> tankUnits;

    // add _units to micro managers
    for (auto & unitTag : m_units)
    {
        const sc2::Unit * unit = m_bot.GetUnit(unitTag);

        BOT_ASSERT(unit, "null unit in addUnitsToMicroManagers()");

        if (unit->unit_type == sc2::UNIT_TYPEID::TERRAN_SIEGETANK || unit->unit_type == sc2::UNIT_TYPEID::TERRAN_SIEGETANKSIEGED)
        {
            tankUnits.push_back(unitTag);
        }
        // TODO: detectors
        else if (Util::IsDetector(*unit) && !m_bot.Data(unit->unit_type).isBuilding)
        {
            detectorUnits.push_back(unitTag);
        }
        // select ranged _units
        else if (Util::GetAttackRange(unit->unit_type, m_bot) >= 1.5f)
        {
            rangedUnits.push_back(unitTag);
        }
        // select melee _units
        else if (Util::GetAttackRange(unit->unit_type, m_bot) < 1.5f)
        {
            meleeUnits.push_back(unitTag);
        }
    }

    m_meleeManager.setUnits(meleeUnits);
    m_rangedManager.setUnits(rangedUnits);
    //m_detectorManager.setUnits(detectorUnits);
    //m_tankManager.setUnits(tankUnits);
}

// TODO: calculates whether or not to regroup
bool Squad::needsToRegroup() const
{
    return false;
}

void Squad::setSquadOrder(const SquadOrder & so)
{
    m_order = so;
}

bool Squad::containsUnit(const UnitTag & u) const
{
    return std::find(m_units.begin(), m_units.end(),u) != m_units.end();
}

void Squad::clear()
{
    for (auto & unitTag : getUnits())
    {
        auto unit = m_bot.GetUnit(unitTag);
        BOT_ASSERT(unit, "null unit in squad clear");

        if (Util::IsWorker(*unit))
        {
            m_bot.Workers().finishedWithWorker(unitTag);
        }
    }

    m_units.clear();
}

bool Squad::isUnitNearEnemy(const UnitTag & unitTag) const
{
    auto unit = m_bot.GetUnit(unitTag);
    BOT_ASSERT(unit, "null unit in squad");

    for (auto & u : m_bot.Observation()->GetUnits())
    {
        if ((Util::GetPlayer(u) == Players::Enemy) && (Util::Dist(unit->pos, u.pos) < 20))
        {
            return true;
        }
    }

    return false;
}

sc2::Point2D Squad::calcCenter() const
{
    if (m_units.empty())
    {
        return sc2::Point2D(0.0f,0.0f);
    }

    sc2::Point2D sum(0,0);
    for (auto & unitTag : m_units)
    {
        auto unit = m_bot.GetUnit(unitTag);
        BOT_ASSERT(unit, "null unit in squad calcCenter");

        sum += unit->pos;
    }

    return sc2::Point2D(sum.x / m_units.size(), sum.y / m_units.size());
}

sc2::Point2D Squad::calcRegroupPosition() const
{
    sc2::Point2D regroup(0.0f,0.0f);

    float minDist = std::numeric_limits<float>::max();

    for (auto & unitTag : m_units)
    {
        auto unit = m_bot.GetUnit(unitTag);

        if (!m_nearEnemy.at(unitTag))
        {
            float dist = Util::Dist(m_order.getPosition(), unit->pos);
            if (dist < minDist)
            {
                minDist = dist;
                regroup = unit->pos;
            }
        }
    }

    if (regroup.x == 0.0f && regroup.y == 0.0f)
    {
        return m_bot.GetStartLocation();
    }
    else
    {
        return regroup;
    }
}

UnitTag Squad::unitClosestToEnemy() const
{
    UnitTag closest = 0;
    float closestDist = std::numeric_limits<float>::max();

    for (auto & unitTag : m_units)
    {
        auto unit = m_bot.GetUnit(unitTag);
        BOT_ASSERT(unit, "null unit");

        // the distance to the order position
        int dist = m_bot.Map().getGroundDistance(unit->pos, m_order.getPosition());

        if (dist != -1 && (!closest || dist < closestDist))
        {
            closest = unitTag;
            closestDist = (float)dist;
        }
    }

    return closest;
}

int Squad::squadUnitsNear(const sc2::Point2D & p) const
{
    int numUnits = 0;

    for (auto & unitTag : m_units)
    {
        auto unit = m_bot.GetUnit(unitTag);
        BOT_ASSERT(unit, "null unit");

        if (Util::Dist(unit->pos, p) < 20.0f)
        {
            numUnits++;
        }
    }

    return numUnits;
}

const std::set<UnitTag> & Squad::getUnits() const
{
    return m_units;
}

const SquadOrder & Squad::getSquadOrder()	const
{
    return m_order;
}

void Squad::addUnit(const UnitTag & u)
{
    m_units.insert(u);
}

void Squad::removeUnit(const UnitTag & u)
{
    m_units.erase(u);
}

const std::string & Squad::getName() const
{
    return m_name;
}