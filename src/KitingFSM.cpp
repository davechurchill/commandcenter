#include "KitingFSM.h"

void KitingFSMState::onUpdate(const sc2::Unit * m_target, CCBot *)
{
}

std::vector<KitingFSMTransition*> KitingFSMState::getTransitions()
{
    return std::vector<KitingFSMTransition*>();
}

KitingFSMState * KitingFSMTransition::getNextState()
{
    return nullptr;
}

bool KitingFSMTransition::isValid(const sc2::Unit * target, CCBot * bot)
{
    return false;
}
