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
    CCPosition      m_position;
    std::string     m_status;

public:

    SquadOrder();
    SquadOrder(int type, const CCPosition & position, float radius, std::string status = "Default");

    const std::string & getStatus() const;
    const CCPosition & getPosition() const;
    const float & getRadius() const;
    const size_t & getType() const;
};