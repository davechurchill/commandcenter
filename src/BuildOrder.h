#pragma once

#include "Common.h"
#include "MetaType.h"

class BuildOrder
{
    std::vector<MetaType> m_buildOrder;

public:

    BuildOrder();
    BuildOrder(const std::vector<MetaType> & buildVector);

    void add(const MetaType & type);
    size_t size() const;
    const MetaType & operator [] (const size_t & index) const;
    MetaType & operator [] (const size_t & index);
};

