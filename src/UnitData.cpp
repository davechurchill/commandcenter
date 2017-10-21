#include "UnitData.h"
#include "Util.h"

UnitData::UnitData()
    : m_mineralsLost(0)
    , m_gasLost(0)
{
    const int maxTypeID = 1024;
    m_numDeadUnits	    = std::vector<int>(maxTypeID + 1, 0);
    m_numUnits		    = std::vector<int>(maxTypeID + 1, 0);
}

void UnitData::updateUnit(const Unit & unit)
{
    bool firstSeen = false;
    const auto & it = m_unitMap.find(unit);
    if (it == m_unitMap.end())
    {
        firstSeen = true;
        m_unitMap[unit] = UnitInfo();
    }

    UnitInfo & ui   = m_unitMap[unit];
    ui.unit         = unit;
    ui.player       = unit.getPlayer();
    ui.lastPosition = unit.getPosition();
    ui.lastHealth   = unit.getHitPoints();
    ui.lastShields  = unit.getShields();
    ui.type         = unit.getType();
    ui.progress     = unit.getBuildPercentage();
    ui.id           = unit.getID();

    if (firstSeen)
    {
        m_numUnits[ui.type]++;
    }
}

void UnitData::killUnit(const Unit & unit)
{
    //_mineralsLost += unit->getType().mineralPrice();
    //_gasLost += unit->getType().gasPrice();
    m_numUnits[unit.getType()]--;
    m_numDeadUnits[unit.getType()]++;

    m_unitMap.erase(unit);
}

void UnitData::removeBadUnits()
{
    for (auto iter = m_unitMap.begin(); iter != m_unitMap.end();)
    {
        if (badUnitInfo(iter->second))
        {
            m_numUnits[iter->second.type]--;
            iter = m_unitMap.erase(iter);
        }
        else
        {
            iter++;
        }
    }
}

bool UnitData::badUnitInfo(const UnitInfo & ui) const
{
    return false;
}

int UnitData::getGasLost() const
{
    return m_gasLost;
}

int UnitData::getMineralsLost() const
{
    return m_mineralsLost;
}

int UnitData::getNumUnits(CCUnitType t) const
{
    return m_numUnits[t];
}

int UnitData::getNumDeadUnits(CCUnitType t) const
{
    return m_numDeadUnits[t];
}

const std::map<Unit, UnitInfo> & UnitData::getUnitInfoMap() const
{
    return m_unitMap;
}