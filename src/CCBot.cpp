#include "sc2api/sc2_api.h"

#include "CCBot.h"
#include "Util.h"

CCBot::CCBot()
    : m_map(*this)
    , m_bases(*this)
    , m_unitInfo(*this)
    , m_workers(*this)
    , m_gameCommander(*this)
    , m_strategy(*this)
    , m_techTree(*this)
{
    
}

void CCBot::OnGameStart() 
{
    m_config.readConfigFile();
    
    // get my race
    auto playerID = Observation()->GetPlayerID();
    for (auto & playerInfo : Observation()->GetGameInfo().player_info)
    {
        if (playerInfo.player_id == playerID)
        {
            m_playerRace[Players::Self] = playerInfo.race_actual;
        }
        else
        {
            m_playerRace[Players::Enemy] = playerInfo.race_requested;
        }
    }
    
    m_techTree.onStart();
    m_strategy.onStart();
    m_map.onStart();
    m_unitInfo.onStart();
    m_bases.onStart();
    m_workers.onStart();

    m_gameCommander.onStart();
}

void CCBot::OnStep()
{
    Control()->GetObservation();

    m_map.onFrame();
    m_unitInfo.onFrame();
    m_bases.onFrame();
    m_workers.onFrame();
    m_strategy.onFrame();

    m_gameCommander.onFrame();

    Debug()->SendDebug();
}

// TODO: Figure out my race
const sc2::Race & CCBot::GetPlayerRace(int player) const
{
    BOT_ASSERT(player == Players::Self || player == Players::Enemy, "invalid player for GetPlayerRace");
    return m_playerRace[player];
}

BotConfig & CCBot::Config()
{
     return m_config;
}

const MapTools & CCBot::Map() const
{
    return m_map;
}

const StrategyManager & CCBot::Strategy() const
{
    return m_strategy;
}

const BaseLocationManager & CCBot::Bases() const
{
    return m_bases;
}

const UnitInfoManager & CCBot::UnitInfo() const
{
    return m_unitInfo;
}

const TypeData & CCBot::Data(const sc2::UnitTypeID & type) const
{
    return m_techTree.getData(type);
}

const TypeData & CCBot::Data(const sc2::UpgradeID & type) const
{
    return m_techTree.getData(type);
}

const TypeData & CCBot::Data(const BuildType & type) const
{
    return m_techTree.getData(type);
}

WorkerManager & CCBot::Workers()
{
    return m_workers;
}

const sc2::Unit * CCBot::GetUnit(const UnitTag & tag) const
{
    return Observation()->GetUnit(tag);
}

sc2::Point2D CCBot::GetStartLocation() const
{
    return Observation()->GetStartLocation();
}

void CCBot::OnError(const std::vector<sc2::ClientError> & client_errors, const std::vector<std::string> & protocol_errors)
{
    
}