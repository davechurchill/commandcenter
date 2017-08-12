#include "BotConfig.h"
#include "rapidjson/document.h"
#include "JSONTools.h"
#include <iostream>

BotConfig::BotConfig()
{
    ConfigFileFound                     = true;
    ConfigFileParsed                    = true;
    ConfigFileLocation                  = "BotConfig.txt";
    BotName                             = "UAlbertaBot";
    Authors                             = "Dave Churchill";
    PrintInfoOnStart                    = false;
    StrategyName                        = "Protoss_ZealotRush";
    ReadDir                             = "read/";
    WriteDir                            = "write/";
    UseEnemySpecificStrategy            = false;
    FoundEnemySpecificStrategy          = false;
    UsingAutoObserver                   = false;

    DrawGameInfo                        = true;
    DrawProductionInfo                  = true;
    DrawTileInfo                        = false;
    DrawWalkableSectors                 = false;
    DrawScoutInfo                       = false;
    DrawResourceInfo                    = false;
    DrawWorkerInfo                      = false;
    DrawModuleTimers                    = false;
    DrawReservedBuildingTiles           = false;
    DrawBuildingInfo                    = false;
    DrawEnemyUnitInfo                   = false;
    DrawLastSeenTileInfo                = false;
    DrawUnitTargetInfo                  = false;
    DrawSquadInfo                       = false;

    KiteWithRangedUnits                 = true;
    ScoutHarassEnemy                    = true;
    CombatUnitsForAttack                = 12;

    ColorLineTarget                     = sc2::Colors::White;
    ColorLineMineral                    = sc2::Colors::Teal;
    ColorUnitNearEnemy                  = sc2::Colors::Red;
    ColorUnitNotNearEnemy               = sc2::Colors::Green;
    
    WorkersPerRefinery                  = 3;
    BuildingSpacing                     = 1;
    PylonSpacing                        = 3;
}

void BotConfig::readConfigFile()
{
    rapidjson::Document doc;

    std::string config = JSONTools::ReadFile(ConfigFileLocation);

    if (config.length() == 0)
    {
        std::cerr << "Error: Config File Not Found or is Empty\n";
        std::cerr << "Config Filename: " << ConfigFileLocation << "\n";
        std::cerr << "The bot will not run without its configuration file\n";
        std::cerr << "Please check that the file exists and is not empty. Incomplete paths are relative to the bot .exe file\n";
        std::cerr << "You can change the config file location in Config::ConfigFile::ConfigFileLocation\n";
        ConfigFileFound = false;
        return;
    }

    bool parsingFailed = doc.Parse(config.c_str()).HasParseError();
    if (parsingFailed)
    {
        std::cerr << "Error: Config File Found, but could not be parsed\n";
        std::cerr << "Config Filename: " << ConfigFileLocation << "\n";
        std::cerr << "The bot will not run without its configuration file\n";
        std::cerr << "Please check that the file exists, is not empty, and is valid JSON. Incomplete paths are relative to the bot .exe file\n";
        std::cerr << "You can change the config file location in Config::ConfigFile::ConfigFileLocation\n";
        ConfigFileParsed = false;
        return;
    }

    // Parse the Bot Info
    if (doc.HasMember("Bot Info") && doc["Bot Info"].IsObject())
    {
        const rapidjson::Value & info = doc["Bot Info"];
        JSONTools::ReadString("BotName", info, BotName);
        JSONTools::ReadString("Authors", info, Authors);
        JSONTools::ReadBool("PrintInfoOnStart", info, PrintInfoOnStart);
    }

    // Parse the Micro Options
    if (doc.HasMember("Micro") && doc["Micro"].IsObject())
    {
        const rapidjson::Value & micro = doc["Micro"];
        JSONTools::ReadBool("KiteWithRangedUnits", micro, KiteWithRangedUnits);
        JSONTools::ReadBool("ScoutHarassEnemy", micro, ScoutHarassEnemy);
        JSONTools::ReadInt("CombatUnitsForAttack", micro, CombatUnitsForAttack);
    }

    // Parse the Macro Options
    if (doc.HasMember("Macro") && doc["Macro"].IsObject())
    {
        const rapidjson::Value & macro = doc["Macro"];
        JSONTools::ReadInt("BuildingSpacing", macro, BuildingSpacing);
        JSONTools::ReadInt("PylongSpacing", macro, PylonSpacing);
        JSONTools::ReadInt("WorkersPerRefinery", macro, WorkersPerRefinery);
    }

    // Parse the Debug Options
    if (doc.HasMember("Debug") && doc["Debug"].IsObject())
    {
        const rapidjson::Value & debug = doc["Debug"];
        JSONTools::ReadBool("DrawGameInfo",             debug, DrawGameInfo);
        JSONTools::ReadBool("DrawTileInfo",             debug, DrawTileInfo);
        JSONTools::ReadBool("DrawBaseLocationInfo",     debug, DrawBaseLocationInfo);
        JSONTools::ReadBool("DrawWalkableSectors",      debug, DrawWalkableSectors);
        JSONTools::ReadBool("DrawResourceInfo",         debug, DrawResourceInfo);
        JSONTools::ReadBool("DrawWorkerInfo",           debug, DrawWorkerInfo);
        JSONTools::ReadBool("DrawProductionInfo",       debug, DrawProductionInfo);
        JSONTools::ReadBool("DrawScoutInfo",            debug, DrawScoutInfo);
        JSONTools::ReadBool("DrawSquadInfo",            debug, DrawSquadInfo);
        JSONTools::ReadBool("DrawBuildingInfo",         debug, DrawBuildingInfo);
        JSONTools::ReadBool("DrawModuleTimers",         debug, DrawModuleTimers);
        JSONTools::ReadBool("DrawEnemyUnitInfo",        debug, DrawEnemyUnitInfo);
        JSONTools::ReadBool("DrawLastSeenTileInfo",     debug, DrawLastSeenTileInfo);
        JSONTools::ReadBool("DrawUnitTargetInfo",       debug, DrawUnitTargetInfo);
        JSONTools::ReadBool("DrawReservedBuildingTiles",debug, DrawReservedBuildingTiles);
    }

    // Parse the Module Options
    if (doc.HasMember("Modules") && doc["Modules"].IsObject())
    {
        const rapidjson::Value & module = doc["Modules"];

        JSONTools::ReadBool("UseAutoObserver", module, UsingAutoObserver);
    }
}

sc2::Race BotConfig::GetRace(const std::string & raceName)
{
    if (raceName == "Protoss")
    {
        return sc2::Race::Protoss;
    }

    if (raceName == "Terran")
    {
        return sc2::Race::Terran;
    }

    if (raceName == "Zerg")
    {
        return sc2::Race::Zerg;
    }

    if (raceName == "Random")
    {
        return sc2::Race::Random;
    }

    BOT_ASSERT(false, "Race not found: %s", raceName.c_str());
    return sc2::Race::Random;
}