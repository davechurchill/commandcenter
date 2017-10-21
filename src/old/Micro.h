#pragma once

#include "Common.h"

class CCBot;

namespace Micro
{   
    void SmartStop          (CCUnit attacker,  CCBot & bot);
    void SmartAttackUnit    (CCUnit attacker,  CCUnit target, CCBot & bot);
    void SmartAttackMove    (CCUnit attacker,  const CCPosition & targetPosition, CCBot & bot);
    void SmartMove          (CCUnit attacker,  const CCPosition & targetPosition, CCBot & bot);
    void SmartMove          (CCUnit attacker,  const CCTilePosition & targetTilePosition, CCBot & bot);
    void SmartRightClick    (const Unit & unit,      CCUnit target, CCBot & bot);
    void SmartRepair        (const Unit & unit,      CCUnit target, CCBot & bot);
    void SmartKiteTarget    (CCUnit rangedUnit,CCUnit target, CCBot & bot);
    void SmartBuild         (CCUnit builder,   const CCUnitType & buildingType, CCTilePosition pos, CCBot & bot);
    void SmartBuildTarget   (CCUnit builder,   const CCUnitType & buildingType, CCUnit target, CCBot & bot);
    void SmartTrain         (CCUnit builder,   const CCUnitType & buildingType, CCBot & bot);
    void SmartAbility       (CCUnit builder,   const sc2::AbilityID & abilityID, CCBot & bot);
};