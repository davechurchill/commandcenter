#pragma once

#include "sc2api/sc2_api.h"

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
    sc2::Race               m_playerRace[2];

    MapTools                m_map;
    BaseLocationManager     m_bases;
    UnitInfoManager         m_unitInfo;
    WorkerManager           m_workers;
    StrategyManager         m_strategy;
    BotConfig               m_config;
    TechTree                m_techTree;

    GameCommander           m_gameCommander;

    void OnError(const std::vector<sc2::ClientError> & client_errors, 
                 const std::vector<std::string> & protocol_errors = {}) override;

public:

    CCBot();
    void OnGameStart() override;
    void OnStep() override;

          BotConfig & Config();
		  void SetConfigFileLocation(std::string configFileLocation);
          WorkerManager & Workers();
    const BaseLocationManager & Bases() const;
    const MapTools & Map() const;
    const UnitInfoManager & UnitInfo() const;
    const StrategyManager & Strategy() const;
    const TypeData & Data(const sc2::UnitTypeID & type) const;
    const TypeData & Data(const sc2::UpgradeID & type) const;
    const TypeData & Data(const BuildType & type) const;
    const sc2::Race & GetPlayerRace(int player) const;
    sc2::Point2D GetStartLocation() const;
    const sc2::Unit * GetUnit(const UnitTag & tag) const;
};