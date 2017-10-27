#include "ShouldFleeTransition.h"
#include "Util.h"
#include "CCBot.h"

ShouldFleeTransition::ShouldFleeTransition(const sc2::Unit * unit, const sc2::Unit * target, KitingFSMState* nextState)
{
    m_unit = unit;
    m_target = target;
    m_nextState = nextState;
}

bool ShouldFleeTransition::isValid(const sc2::Unit * target, CCBot * bot)
{
    sc2::UnitTypeData unitTypeData = bot->Observation()->GetUnitTypeData()[m_unit->unit_type];

    // use the correct weapon range regardless of target type
    float range(Util::GetAttackRangeForTarget(m_unit, target, *bot));
    float dist(Util::Dist(m_unit->pos, target->pos));
    float timeUntilAttacked = std::max(0.f, (dist - range) / unitTypeData.movement_speed);

    return Util::IsCombatUnitType(target->unit_type, *bot) && !(timeUntilAttacked >= m_unit->weapon_cooldown);
}
KitingFSMState* ShouldFleeTransition::getNextState()
{
    return m_nextState;
}

void ShouldFleeTransition::onTransition() { }