#include "FireClosestFSMState.h"
#include "PullBackFSMState.h"
#include "ShouldPullBackTransition.h"
#include "CCBot.h"

FireClosestFSMState::FireClosestFSMState(const sc2::Unit * unit)
{
    m_unit = unit;
}

void FireClosestFSMState::onEnter(const std::vector<const sc2::Unit*> *, CCBot*)
{
    FocusFireFSMState* pullBack = new PullBackFSMState(m_unit);
    FocusFireFSMTransition* shouldPull = new ShouldPullBackTransition(m_unit, pullBack);
    transitions = { shouldPull };
}
void FireClosestFSMState::onExit() {}
std::vector<FocusFireFSMTransition*> FireClosestFSMState::getTransitions()
{
    return transitions;
}
void FireClosestFSMState::onUpdate(const sc2::Unit * target, CCBot* bot) 
{
    bot->Actions()->UnitCommand(m_unit, sc2::ABILITY_ID::ATTACK_ATTACK, target);
}
