#pragma once

#include "Common.h"

struct UnitInfo
{
    // we need to store all of this data because if the unit is not visible, we
    // can't reference it from the unit pointer

    CCUnitID        id;
    float           lastHealth;
    float           lastShields;
    int             player;
    CCUnit          unit;
    sc2::Point3D    lastPosition;
    CCUnitType      type;
    float           progress;

    UnitInfo()
        : id(0)
        , lastHealth(0)
        , player(-1)
        , lastPosition(sc2::Point3D(0, 0, 0))
        , type(0)
        , progress(1.0)
    {

    }

    bool operator == (CCUnit unit) const
    {
#ifdef SC2API
        return id == unit->tag;
#else
        return id == unit->getID();
#endif
    }

    bool operator == (const UnitInfo & rhs) const
    {
        return (id == rhs.id);
    }

    bool operator < (const UnitInfo & rhs) const
    {
        return (id < rhs.id);
    }
};

typedef std::vector<UnitInfo> UnitInfoVector;

class UnitData
{
    std::map<CCUnit, UnitInfo> m_unitMap;
    std::vector<int>        m_numDeadUnits;
    std::vector<int>        m_numUnits;
    int                     m_mineralsLost;
    int	                    m_gasLost;

    bool badUnitInfo(const UnitInfo & ui) const;

public:

    UnitData();

    void	updateUnit(CCUnit unit);
    void	killUnit(CCUnit unit);
    void	removeBadUnits();

    int		getGasLost()                                const;
    int		getMineralsLost()                           const;
    int		getNumUnits(CCUnitType t)              const;
    int		getNumDeadUnits(CCUnitType t)          const;
    const	std::map<CCUnit, UnitInfo> & getUnitInfoMap()  const;
};
