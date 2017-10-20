#pragma once

#include "Common.h"

class CCBot;

class Unit
{
    CCBot &     m_bot;
    CCUnit      m_unit;
    CCUnitID    m_unitID;

public:

    Unit(CCUnit unit, CCBot & bot);

    CCUnit getRawUnit() const;

    const CCPosition & pos() const;
    const CCHealth & health() const;
};
