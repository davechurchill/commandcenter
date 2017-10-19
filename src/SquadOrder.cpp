#include "SquadOrder.h"

SquadOrder::SquadOrder()
    : m_type    (SquadOrderTypes::None)
    , m_radius  (0)
{
}

SquadOrder::SquadOrder(int type, const CCPosition & position, float radius, std::string status)
    : m_type    (type)
    , m_position(position)
    , m_radius  (radius)
    , m_status  (status)
{
}

const std::string & SquadOrder::getStatus() const
{
    return m_status;
}

const CCPosition & SquadOrder::getPosition() const
{
    return m_position;
}

const float & SquadOrder::getRadius() const
{
    return m_radius;
}

const size_t & SquadOrder::getType() const
{
    return m_type;
}