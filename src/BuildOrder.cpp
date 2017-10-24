#include "BuildOrder.h"

BuildOrder::BuildOrder()
{

}


BuildOrder::BuildOrder(const std::vector<MetaType> & vec)
    : m_buildOrder(vec)
{

}

void BuildOrder::add(const MetaType & type)
{
    m_buildOrder.push_back(type);
}

size_t BuildOrder::size() const
{
    return m_buildOrder.size();
}

const MetaType & BuildOrder::operator [] (const size_t & index) const
{
    return m_buildOrder[index];
}

MetaType & BuildOrder::operator [] (const size_t & index)
{
    return m_buildOrder[index];
}