#pragma once

#include "Common.h"

namespace BuildingStatus
{
    enum { Unassigned = 0, Assigned = 1, UnderConstruction = 2, Size = 3 };
}

class Building
{
public:

    sc2::Point2D    desiredPosition;
    sc2::Point2D    finalPosition;
    sc2::Point2D    position;
    sc2::UnitTypeID type;
    const sc2::Unit * buildingUnit;
    const sc2::Unit * builderUnit;
    size_t          status;
    int             lastOrderFrame;
    bool            buildCommandGiven;
    bool            underConstruction;

    Building();

    // constructor we use most often
    Building(sc2::UnitTypeID t, sc2::Point2D desired);

    // equals operator
    bool operator == (const Building & b);
};
