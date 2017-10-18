#include "FocusFireFSM.h"
/*
Duds so the compiler shuts up.
*/

void FocusFireFSMState::onUpdate(const sc2::Unit * m_target, CCBot* bot)
{
}

void FocusFireFSMState::onEnter(const std::vector<const sc2::Unit*> *, CCBot *)
{
}

std::vector<FocusFireFSMTransition*> FocusFireFSMState::getTransitions()
{
    return std::vector<FocusFireFSMTransition*>();
}

FocusFireFSMState * FocusFireFSMTransition::getNextState()
{
    return nullptr;
}

bool FocusFireFSMTransition::isValid(std::map<sc2::Tag, float> *, CCBot*)
{
    return false;
}
