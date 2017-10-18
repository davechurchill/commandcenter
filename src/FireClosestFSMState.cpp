#include "FireClosestFSMState.h"
#include "CCBot.h"

FireClosestFSMState::FireClosestFSMState(const sc2::Unit * unit, const std::vector<const sc2::Unit*> * units, const sc2::Unit * target)
{
    m_unit = unit;
    m_units = units;
    m_target = target;
}

void FireClosestFSMState::onEnter() 
{
    FocusFireFSMState* pullBack = new PullBackFSMState(m_unit, m_units, m_target);
    FocusFireFSMTransition* shouldPull = new ShouldPullBackTransition(m_unit, m_units, m_target, pullBack);
    transitions = { shouldPull };
}
void FireClosestFSMState::onExit() {}
std::vector<FocusFireFSMTransition*> FireClosestFSMState::getTransitions()
{
    return transitions;
}
void FireClosestFSMState::onUpdate(const sc2::Unit * target, CCBot* bot) 
{
    m_target = target;
    bot->Actions()->UnitCommand(m_unit, sc2::ABILITY_ID::ATTACK_ATTACK, target);
}
