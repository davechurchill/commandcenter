#pragma once

#include "Common.h"
#include "Building.h"

class BuildingData
{
    std::vector<Building>                   _buildings;

public:

    BuildingData();

    std::vector<Building> & getBuildings();

    void addBuilding(const Building & b);
    void removeBuilding(const Building & b);
    void removeBuildings(const std::vector<Building> & buildings);
    bool isBeingBuilt(UnitType type);
};