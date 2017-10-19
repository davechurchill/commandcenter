#pragma once

#include "sc2api/sc2_api.h"

#include "UnitData.h"
#include "BaseLocation.h"

class CCBot;
class UnitInfoManager 
{
    CCBot &           m_bot;

    std::map<int, UnitData> m_unitData;

    std::map<int, std::vector<CCUnit>> m_units;

    void                    updateUnit(CCUnit unit);
    void                    updateUnitInfo();
    bool                    isValidUnit(CCUnit unit);
    
    const UnitData &        getUnitData(int player) const;

    void drawSelectedUnitDebugInfo();

public:

    UnitInfoManager(CCBot & bot);

    void                    onFrame();
    void                    onStart();

    const std::vector<CCUnit> & getUnits(int player) const;

    size_t                  getUnitTypeCount(int player, CCUnitType type, bool completed = true) const;

    void                    getNearbyForce(std::vector<UnitInfo> & unitInfo, CCPosition p, int player, float radius) const;

    const std::map<CCUnit, UnitInfo> & getUnitInfoMap(int player) const;

    //bool                  enemyHasCloakedUnits() const;
    void                    drawUnitInformation(float x, float y) const;

};