#pragma once

#include "Common.h"
#include "sc2api/sc2_api.h"

class CCBot;

namespace Micro
{   
    void SmartStop      (const UnitTag & attacker,  CCBot & bot);
    void SmartAttackUnit(const UnitTag & attacker,  const UnitTag & target, CCBot & bot);
    void SmartAttackMove(const UnitTag & attacker,  const sc2::Point2D & targetPosition, CCBot & bot);
    void SmartMove      (const UnitTag & attacker,  const sc2::Point2D & targetPosition, CCBot & bot);
    void SmartRightClick(const UnitTag & unit,      const UnitTag & target, CCBot & bot);
    void SmartRepair    (const UnitTag & unit,      const UnitTag & target, CCBot & bot);
    void SmartKiteTarget(const UnitTag & rangedUnit,const UnitTag & target, CCBot & bot);
    void SmartBuild     (const UnitTag & builder,   const sc2::UnitTypeID & buildingType, sc2::Point2D pos, CCBot & bot);
    void SmartBuildTag  (const UnitTag & builder,   const sc2::UnitTypeID & buildingType, UnitTag targetTag, CCBot & bot);
    void SmartTrain     (const UnitTag & builder,   const sc2::UnitTypeID & buildingType, CCBot & bot);
    void SmartAbility   (const UnitTag & builder,   const sc2::AbilityID & abilityID, CCBot & bot);
};