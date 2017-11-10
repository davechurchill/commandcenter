#include "StrategyManager.h"
#include "CCBot.h"
#include "JSONTools.h"
#include "Util.h"
#include "MetaType.h"

Strategy::Strategy()
{

}

Strategy::Strategy(const std::string & name, const CCRace & race, const BuildOrder & buildOrder)
    : m_name(name)
    , m_race(race)
    , m_buildOrder(buildOrder)
    , m_wins(0)
    , m_losses(0)
{

}

// constructor
StrategyManager::StrategyManager(CCBot & bot)
    : m_bot(bot)
{

}

void StrategyManager::onStart()
{
    readStrategyFile(m_bot.Config().ConfigFileLocation);
}

void StrategyManager::onFrame()
{

}

const BuildOrder & StrategyManager::getOpeningBookBuildOrder() const
{
    auto buildOrderIt = m_strategies.find(m_bot.Config().StrategyName);

    // look for the build order in the build order map
    if (buildOrderIt != std::end(m_strategies))
    {
        return (*buildOrderIt).second.m_buildOrder;
    }
    else
    {
        BOT_ASSERT(false, "Strategy not found: %s, returning empty initial build order", m_bot.Config().StrategyName.c_str());
        return m_emptyBuildOrder;
    }
}

bool StrategyManager::shouldExpandNow() const
{
    return false;
}

void StrategyManager::addStrategy(const std::string & name, const Strategy & strategy)
{
    m_strategies[name] = strategy;
}

const UnitPairVector StrategyManager::getBuildOrderGoal() const
{
    return std::vector<UnitPair>();
}

const UnitPairVector StrategyManager::getProtossBuildOrderGoal() const
{
    return std::vector<UnitPair>();
}

const UnitPairVector StrategyManager::getTerranBuildOrderGoal() const
{
    return std::vector<UnitPair>();
}

const UnitPairVector StrategyManager::getZergBuildOrderGoal() const
{
    return std::vector<UnitPair>();
}


void StrategyManager::onEnd(const bool isWinner)
{

}

void StrategyManager::readStrategyFile(const std::string & filename)
{
    CCRace race = m_bot.GetPlayerRace(Players::Self);
    std::string ourRace = Util::GetStringFromRace(race);

    std::ifstream file(filename);
    json j;
    file >> j;

#ifdef SC2API
    const char * strategyObject = "SC2API Strategy";
#else
    const char * strategyObject = "BWAPI Strategy";
#endif

    // Parse the Strategy Options
    if (j.count(strategyObject) && j[strategyObject].is_object())
    {
        const json & strategy = j[strategyObject];

        // read in the various strategic elements
        JSONTools::ReadBool("ScoutHarassEnemy", strategy, m_bot.Config().ScoutHarassEnemy);
        JSONTools::ReadString("ReadDirectory", strategy, m_bot.Config().ReadDir);
        JSONTools::ReadString("WriteDirectory", strategy, m_bot.Config().WriteDir);

        // if we have set a strategy for the current race, use it
        if (strategy.count(ourRace.c_str()) && strategy[ourRace.c_str()].is_string())
        {
            m_bot.Config().StrategyName = strategy[ourRace.c_str()].get<std::string>();
        }

        // check if we are using an enemy specific strategy
        JSONTools::ReadBool("UseEnemySpecificStrategy", strategy, m_bot.Config().UseEnemySpecificStrategy);
        if (m_bot.Config().UseEnemySpecificStrategy && strategy.count("EnemySpecificStrategy") && strategy["EnemySpecificStrategy"].is_object())
        {
            // TODO: Figure out enemy name
            const std::string enemyName = "ENEMY NAME";
            const json & specific = strategy["EnemySpecificStrategy"];

            // check to see if our current enemy name is listed anywhere in the specific strategies
            if (specific.count(enemyName.c_str()) && specific[enemyName.c_str()].is_object())
            {
                const json & enemyStrategies = specific[enemyName.c_str()];

                // if that enemy has a strategy listed for our current race, use it
                if (enemyStrategies.count(ourRace.c_str()) && enemyStrategies[ourRace.c_str()].is_string())
                {
                    m_bot.Config().StrategyName = enemyStrategies[ourRace.c_str()].get<std::string>();
                    m_bot.Config().FoundEnemySpecificStrategy = true;
                }
            }
        }

        // Parse all the Strategies
        if (strategy.count("Strategies") && strategy["Strategies"].is_object())
        {
            const json & strategies = strategy["Strategies"];
            for (auto it = strategies.begin(); it != strategies.end(); ++it) 
            {
                const std::string & name = it.key();
                const json & val = it.value();

                std::cout << val << "\n";

                CCRace strategyRace;
                if (val.count("Race") && val["Race"].is_string())
                {
                    strategyRace = Util::GetRaceFromString(val["Race"].get<std::string>());
                }
                else
                {
                    BOT_ASSERT(false, "Strategy must have a Race string: %s", name.c_str());
                    continue;
                }

                BuildOrder buildOrder;
                if (val.count("OpeningBuildOrder") && val["OpeningBuildOrder"].is_array())
                {
                    const json & build = val["OpeningBuildOrder"];

                    for (size_t b(0); b < build.size(); b++)
                    {
                        if (build[b].is_string())
                        {
                            MetaType MetaType(build[b].get<std::string>(), m_bot);
                            buildOrder.add(MetaType);
                        }
                        else
                        {
                            BOT_ASSERT(false, "Build order item must be a string %s", name.c_str());
                            continue;
                        }
                    }
                }

                addStrategy(name, Strategy(name, strategyRace, buildOrder));
            }
        }
    }
}