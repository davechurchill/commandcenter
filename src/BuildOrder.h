#pragma once

#include "Common.h"

class BuildOrder
{
    sc2::Race m_race;
    std::vector<sc2::UnitTypeID> m_buildOrder;

public:

    BuildOrder();
    BuildOrder(const sc2::Race & race);
    BuildOrder(const sc2::Race & race, const std::vector<sc2::UnitTypeID> & metaVector);

    void add(const sc2::UnitTypeID & type);
    const size_t size() const;
    const sc2::Race & getRace() const;
    const sc2::UnitTypeID & operator [] (const size_t & index) const;
    sc2::UnitTypeID & operator [] (const size_t & index);
};

