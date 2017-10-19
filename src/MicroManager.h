#pragma once

#include "Common.h"
#include "SquadOrder.h"
#include "Micro.h"

struct AirThreat
{
    CCUnit unit;
    double weight;
};

struct GroundThreat
{
    CCUnit unit;
    double weight;
};

class CCBot;

class MicroManager
{
    std::vector<CCUnit> m_units;

protected:

    CCBot & m_bot;
    SquadOrder order;

    virtual void executeMicro(const std::vector<CCUnit> & targets) = 0;
    void trainSubUnits(CCUnit unit) const;


public:

    MicroManager(CCBot & bot);

    const std::vector<CCUnit> & getUnits() const;

    void setUnits(const std::vector<CCUnit> & u);
    void execute(const SquadOrder & order);
    void regroup(const CCPosition & regroupPosition) const;

};