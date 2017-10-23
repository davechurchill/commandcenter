#include "FleeFSMState.h"
#include "AttackFSMState.h"
#include "ShouldAttackTransition.h"
#include "CCBot.h"

FleeFSMState::FleeFSMState(const sc2::Unit * unit, const sc2::Unit * target)
{
    m_unit = unit;
    m_target = target;
}

void FleeFSMState::onEnter()
{
    KitingFSMState* attack = new AttackFSMState(m_unit, m_target);
    KitingFSMTransition* shouldAttack = new ShouldAttackTransition(m_unit, m_target, attack);
    transitions = { shouldAttack };
}
void FleeFSMState::onExit() {}
std::vector<KitingFSMTransition*> FleeFSMState::getTransitions()
{
    return transitions;
}
void FleeFSMState::onUpdate(const sc2::Unit * target, CCBot* bot)
{
    sc2::Point2D fleePosition(m_unit->pos - target->pos + m_unit->pos);
    bot->Actions()->UnitCommand(m_unit, sc2::ABILITY_ID::MOVE, fleePosition);
}
