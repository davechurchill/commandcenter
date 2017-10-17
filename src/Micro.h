#pragma once

#include "Common.h"
#include "sc2api/sc2_api.h"
#include "FocusFireFiniteStateMachine.h";

class CCBot;
namespace Micro
{   
    void SmartStop          (const sc2::Unit * attacker,  CCBot & bot);
    void SmartAttackUnit    (const sc2::Unit * attacker,  const sc2::Unit * target, CCBot & bot);
    void SmartAttackMove    (const sc2::Unit * attacker,  const sc2::Point2D & targetPosition, CCBot & bot);
    void SmartMove          (const sc2::Unit * attacker,  const sc2::Point2D & targetPosition, CCBot & bot);
    void SmartRightClick    (const sc2::Unit * unit,      const sc2::Unit * target, CCBot & bot);
    void SmartRepair        (const sc2::Unit * unit,      const sc2::Unit * target, CCBot & bot);
    void SmartKiteTarget    (const sc2::Unit * rangedUnit,const sc2::Unit * target, CCBot & bot);
	void SmartFocusFire(const sc2::Unit * rangedUnit, const std::vector<const sc2::Unit *> rangedUnits, const sc2::Unit * target, CCBot & bot, std::map<sc2::Tag, FSMState*> &states);
    void SmartBuild         (const sc2::Unit * builder,   const sc2::UnitTypeID & buildingType, sc2::Point2D pos, CCBot & bot);
    void SmartBuildTarget   (const sc2::Unit * builder,   const sc2::UnitTypeID & buildingType, const sc2::Unit * target, CCBot & bot);
    void SmartTrain         (const sc2::Unit * builder,   const sc2::UnitTypeID & buildingType, CCBot & bot);
    void SmartAbility       (const sc2::Unit * builder,   const sc2::AbilityID & abilityID, CCBot & bot);
};