#include "PullBackFSMState.h"
#include "CCBot.h"

PullBackFSMState::PullBackFSMState(const sc2::Unit * unit, const std::vector<const sc2::Unit*> * units, const sc2::Unit * target)
{
    m_unit = unit;
    m_units = units;
    m_target = target;
}

void PullBackFSMState::onEnter() 
{
    m_position = ((m_unit->pos - m_target->pos) / 2) + m_unit->pos;
    CCFSMState* fireClosest = new FireClosestFSMState(m_unit, m_units, m_target);
    CCFSMTransition* donePull = new DonePullBackTransition(m_unit, m_position, fireClosest);
    this->transitions = { donePull };
}
void PullBackFSMState::onExit() {}
std::vector<CCFSMTransition*> PullBackFSMState::getTransitions()
{
    return transitions;
}
void PullBackFSMState::onUpdate(const sc2::Unit * target, CCBot* bot)
{
    bot->Actions()->UnitCommand(m_unit, sc2::ABILITY_ID::MOVE, m_position);
}
