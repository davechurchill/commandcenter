#pragma once

#include "Common.h"
#include "BuildType.h"

class BuildOrder
{
    sc2::Race m_race;
    std::vector<BuildType> m_buildOrder;

public:

    BuildOrder();
    BuildOrder(const sc2::Race & race);
    BuildOrder(const sc2::Race & race, const std::vector<BuildType> & buildVector);

    void add(const BuildType & type);
    size_t size() const;
    const sc2::Race & getRace() const;
    const BuildType & operator [] (const size_t & index) const;
    BuildType & operator [] (const size_t & index);
};

