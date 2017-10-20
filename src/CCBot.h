#pragma once

#include "Common.h"

#include "MapTools.h"
#include "BaseLocationManager.h"
#include "UnitInfoManager.h"
#include "WorkerManager.h"
#include "BotConfig.h"
#include "GameCommander.h"
#include "BuildingManager.h"
#include "StrategyManager.h"
#include "TechTree.h"
#include "BuildType.h"

class CCBot : public sc2::Agent 
{
    CCRace                  m_playerRace[2];

    MapTools                m_map;
    BaseLocationManager     m_bases;
    UnitInfoManager         m_unitInfo;
    WorkerManager           m_workers;
    StrategyManager         m_strategy;
    BotConfig               m_config;
    TechTree                m_techTree;
    GameCommander           m_gameCommander;

    std::vector<CCUnit>     m_allUnits;

    void setUnits();
    void OnError(const std::vector<sc2::ClientError> & client_errors, 
                 const std::vector<std::string> & protocol_errors = {}) override;

public:

    CCBot();
    void OnGameStart() override;
    void OnStep() override;

          BotConfig & Config();
          WorkerManager & Workers();
    const BaseLocationManager & Bases() const;
    const MapTools & Map() const;
    const UnitInfoManager & UnitInfo() const;
    const StrategyManager & Strategy() const;
    const TypeData & Data(const CCUnitType & type) const;
    const TypeData & Data(const sc2::UpgradeID & type) const;
    const TypeData & Data(const BuildType & type) const;
    const TypeData & Data(CCUnit unit) const;
    const CCRace & GetPlayerRace(int player) const;
    CCPosition GetStartLocation() const;

    int GetMinerals() const;
    int GetGas() const;
    CCUnit GetUnit(const CCUnitID & tag) const;
    const std::vector<CCUnit> & GetUnits() const;
    const std::vector<CCPosition> & GetEnemyStartLocations() const;

#ifdef SC2API

#else

#endif
};