#pragma once

#include "Common.h"

struct UnitInfo
{
    // we need to store all of this data because if the unit is not visible, we
    // can't reference it from the unit pointer

    UnitTag         tag;
    float           lastHealth;
    float           lastShields;
    int             player;
    const sc2::Unit * unit;
    sc2::Point3D    lastPosition;
    sc2::UnitTypeID type;
    float           progress;

    UnitInfo()
        : tag(0)
        , lastHealth(0)
        , player(-1)
        , lastPosition(sc2::Point3D(0, 0, 0))
        , type(0)
        , progress(1.0)
    {

    }

    bool operator == (sc2::Unit * unit) const
    {
        return tag == unit->tag;
    }

    bool operator == (const UnitInfo & rhs) const
    {
        return (tag == rhs.tag);
    }

    bool operator < (const UnitInfo & rhs) const
    {
        return (tag < rhs.tag);
    }
};

typedef std::vector<UnitInfo> UnitInfoVector;

class UnitData
{
    std::map<const sc2::Unit *, UnitInfo> m_unitMap;
    std::vector<int>        m_numDeadUnits;
    std::vector<int>        m_numUnits;
    int                     m_mineralsLost;
    int	                    m_gasLost;

    bool badUnitInfo(const UnitInfo & ui) const;

public:

    UnitData();

    void	updateUnit(const sc2::Unit * unit);
    void	killUnit(const sc2::Unit * unit);
    void	removeBadUnits();

    int		getGasLost()                                const;
    int		getMineralsLost()                           const;
    int		getNumUnits(sc2::UnitTypeID t)              const;
    int		getNumDeadUnits(sc2::UnitTypeID t)          const;
    const	std::map<const sc2::Unit *, UnitInfo> & getUnitInfoMap()  const;
};
