#include "AttackFSMState.h"
#include "FleeFSMState.h"
#include "ShouldFleeTransition.h"
#include "CCBot.h"

AttackFSMState::AttackFSMState(const sc2::Unit * unit, const sc2::Unit * target)
{
    m_unit = unit;
    m_target = target;
}

void AttackFSMState::onEnter()
{
    KitingFSMState* flee = new FleeFSMState(m_unit, m_target);
    KitingFSMTransition* shouldFlee = new ShouldFleeTransition(m_unit, m_target, flee);
    transitions = { shouldFlee };
}
void AttackFSMState::onExit() {}
std::vector<KitingFSMTransition*> AttackFSMState::getTransitions()
{
    return transitions;
}
void AttackFSMState::onUpdate(const sc2::Unit * target, CCBot* bot)
{
    m_target = target;
    bot->Actions()->UnitCommand(m_unit, sc2::ABILITY_ID::ATTACK_ATTACK, target);
}
