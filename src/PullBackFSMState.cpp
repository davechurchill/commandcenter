#include "PullBackFSMState.h"
#include "FireClosestFSMState.h"
#include "DonePullBackTransition.h"
#include "CCBot.h"
#include "Util.h"
#include <algorithm>

PullBackFSMState::PullBackFSMState(const sc2::Unit * unit, const sc2::Unit * target)
{
    m_unit = unit;
    m_target = target;
}

void PullBackFSMState::onEnter(const std::vector<const sc2::Unit*> * targets, CCBot* bot)
{
    auto targetWeapons = bot->Observation()->GetUnitTypeData()[m_target->unit_type].weapons;
    float targetRange = 0.f;
    for (auto weapon : targetWeapons) targetRange = std::max(weapon.range, targetRange);

    sc2::Point2D closestTarget = targets->at(0)->pos;
    for (auto target : *targets)
        if (Util::Dist(target->pos, m_unit->pos) < Util::Dist(closestTarget, m_unit->pos))
            closestTarget = target->pos;

    sc2::Point2D direction = m_unit->pos - closestTarget;// ((closestTarget + Util::CalcCenter(*targets)) / 2);
    Util::Normalize(direction);
    m_position = (direction * (targetRange + 2.f)) + closestTarget;

    FocusFireFSMState* fireClosest = new FireClosestFSMState(m_unit, m_target);
    FocusFireFSMTransition* donePull = new DonePullBackTransition(m_unit, m_position, fireClosest);
    this->transitions = { donePull };
}
void PullBackFSMState::onExit() {}
std::vector<FocusFireFSMTransition*> PullBackFSMState::getTransitions()
{
    return transitions;
}
void PullBackFSMState::onUpdate(const sc2::Unit * target, CCBot* bot)
{
    bot->Actions()->UnitCommand(m_unit, sc2::ABILITY_ID::MOVE, m_position);
}
