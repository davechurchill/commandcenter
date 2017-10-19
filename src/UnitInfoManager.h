#pragma once

#include "Common.h"
#include "UnitData.h"
#include "BaseLocation.h"

class CCBot;
class UnitInfoManager 
{
    CCBot &           m_bot;

    std::map<CCPlayer, UnitData> m_unitData; 
    std::map<CCPlayer, std::vector<CCUnit>> m_units;

    void                    updateUnit(CCUnit unit);
    void                    updateUnitInfo();
    bool                    isValidUnit(CCUnit unit);
    
    const UnitData &        getUnitData(CCPlayer player) const;

    void drawSelectedUnitDebugInfo();

public:

    UnitInfoManager(CCBot & bot);

    void                    onFrame();
    void                    onStart();

    const std::vector<CCUnit> & getUnits(CCPlayer player) const;

    size_t                  getUnitTypeCount(CCPlayer player, CCUnitType type, bool completed = true) const;

    void                    getNearbyForce(std::vector<UnitInfo> & unitInfo, CCPosition p, int player, float radius) const;

    const std::map<CCUnit, UnitInfo> & getUnitInfoMap(CCPlayer player) const;

    //bool                  enemyHasCloakedUnits() const;
    void                    drawUnitInformation(float x, float y) const;

};