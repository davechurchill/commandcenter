#include "BuildOrder.h"

BuildOrder::BuildOrder()
    : m_race(sc2::Race::Protoss)
{

}

BuildOrder::BuildOrder(const sc2::Race & race)
    : m_race(race)
{

}

BuildOrder::BuildOrder(const sc2::Race & race, const std::vector<BuildType> & vec)
    : m_race(race)
    , m_buildOrder(vec)
{

}

void BuildOrder::add(const BuildType & type)
{
    m_buildOrder.push_back(type);
}

const sc2::Race & BuildOrder::getRace() const
{
    return m_race;
}

size_t BuildOrder::size() const
{
    return m_buildOrder.size();
}

const BuildType & BuildOrder::operator [] (const size_t & index) const
{
    return m_buildOrder[index];
}

BuildType & BuildOrder::operator [] (const size_t & index)
{
    return m_buildOrder[index];
}