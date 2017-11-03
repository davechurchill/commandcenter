#include "ShouldPullBackTransition.h"
#include "Util.h"
#include "CCBot.h"

ShouldPullBackTransition::ShouldPullBackTransition(const sc2::Unit * unit, FocusFireFSMState* nextState)
{
    m_unit = unit;
    m_nextState = nextState;
}

bool ShouldPullBackTransition::isValid(const sc2::Unit * target, const std::vector<const sc2::Unit*> * units, std::unordered_map<sc2::Tag, float> * unitHealth, CCBot* bot)
{
    //update health in the health map
    if (unitHealth->find(m_unit->tag) == unitHealth->end())
        unitHealth->insert_or_assign(m_unit->tag, m_unit->health);
    float previousHealth = unitHealth->at(m_unit->tag);
    unitHealth->insert_or_assign(m_unit->tag, m_unit->health);

    float damage = Util::GetAttackDamageForTarget(target, m_unit, *bot);
    float unitdamage = Util::GetAttackDamageForTarget(m_unit, target, *bot);

    //condition 1: if this unit would get killed by 1 attack from the target and there is no other unit closer to the target, this unit should back
    if (m_unit->health <= damage)
    {
        float dist = Util::Dist(m_unit->pos, target->pos);
        if (dist <= Util::GetAttackRangeForTarget(target, m_unit, *bot))
        {
            bool otherUnitCloser = false;
            for (const sc2::Unit* unit : *units)
            {
                if (unit != m_unit && Util::Dist(unit->pos, target->pos) < dist)
                {
                    //no need to pull back, since another unit is closer to target
                    otherUnitCloser = true;
                    break;
                }
            }
            if (!otherUnitCloser)
            {
                return true;
            }
        }
    }

    //condition 2: if the unit just got hit and it would die in 2 attacks from the target, it should back
    return previousHealth > m_unit->health && m_unit->health <= (damage * 2);
}
FocusFireFSMState* ShouldPullBackTransition::getNextState()
{
    return m_nextState;
}

void ShouldPullBackTransition::onTransition() { }