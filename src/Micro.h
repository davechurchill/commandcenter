#pragma once

#include "Common.h"
#include "sc2api/sc2_api.h"

class CCBot;

namespace Micro
{   
    void SmartStop          (CCUnit attacker,  CCBot & bot);
    void SmartAttackUnit    (CCUnit attacker,  CCUnit target, CCBot & bot);
    void SmartAttackMove    (CCUnit attacker,  const sc2::Point2D & targetPosition, CCBot & bot);
    void SmartMove          (CCUnit attacker,  const sc2::Point2D & targetPosition, CCBot & bot);
    void SmartRightClick    (CCUnit unit,      CCUnit target, CCBot & bot);
    void SmartRepair        (CCUnit unit,      CCUnit target, CCBot & bot);
    void SmartKiteTarget    (CCUnit rangedUnit,CCUnit target, CCBot & bot);
    void SmartBuild         (CCUnit builder,   const CCUnitType & buildingType, sc2::Point2D pos, CCBot & bot);
    void SmartBuildTarget   (CCUnit builder,   const CCUnitType & buildingType, CCUnit target, CCBot & bot);
    void SmartTrain         (CCUnit builder,   const CCUnitType & buildingType, CCBot & bot);
    void SmartAbility       (CCUnit builder,   const sc2::AbilityID & abilityID, CCBot & bot);
};