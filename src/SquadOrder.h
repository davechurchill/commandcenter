#pragma once

#include "Common.h"


namespace SquadOrderTypes
{
    enum { None, Idle, Attack, Defend, Regroup, Drop, SquadOrderTypes };
}

class SquadOrder
{
    size_t          m_type;
    float           m_radius;
    sc2::Point2D    m_position;
    std::string     m_status;

public:

    SquadOrder();
    SquadOrder(int type, const sc2::Point2D & position, float radius, std::string status = "Default");

    const std::string & getStatus() const;
    const sc2::Point2D & getPosition() const;
    const float & getRadius() const;
    const size_t & getType() const;
};