#pragma once

#include "Common.h"
#include "Util.h"
#include "Unit.h"
#include "UnitType.h"

struct UnitInfo
{
    // we need to store all of this data because if the unit is not visible, we
    // can't reference it from the unit pointer

    CCUnitID        id;
    CCHealth        lastHealth;
    CCHealth        lastShields;
    CCPlayer        player;
    Unit            unit;
    CCPosition      lastPosition;
    UnitType        type;
    float           progress;

    UnitInfo()
        : id(0)
        , lastHealth(0)
        , player(-1)
        , lastPosition(0, 0)
        , progress(1.0)
    {

    }

    bool operator == (const Unit & unit) const
    {
        return id == unit.getID();
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
    std::map<Unit, UnitInfo>    m_unitMap;
    std::map<UnitType, int>     m_numDeadUnits;
    std::map<UnitType, int>     m_numUnits;
    int                         m_mineralsLost;
    int	                        m_gasLost;

    bool badUnitInfo(const UnitInfo & ui) const;

public:

    UnitData();

    void	updateUnit(const Unit & unit);
    void	killUnit(const Unit & unit);
    void	removeBadUnits();

    int		getGasLost()                                const;
    int		getMineralsLost()                           const;
    int		getNumUnits(const UnitType & t)              const;
    int		getNumDeadUnits(const UnitType & t)          const;
    const	std::map<Unit, UnitInfo> & getUnitInfoMap()  const;
};
