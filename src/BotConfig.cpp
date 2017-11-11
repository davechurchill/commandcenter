#include "BotConfig.h"
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

    SetLocalSpeed                       = 10;
    SetFrameSkip                        = 0;
    UserInput                           = true;
    CompleteMapInformation              = false;

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

    ColorLineTarget                     = CCColor(255, 255, 255);
    ColorLineMineral                    = CCColor(0, 128, 128);
    ColorUnitNearEnemy                  = CCColor(255, 0, 0);
    ColorUnitNotNearEnemy               = CCColor(0, 255, 0);
    
    WorkersPerRefinery                  = 3;
    BuildingSpacing                     = 1;
    PylonSpacing                        = 3;
}

void BotConfig::readConfigFile()
{
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

    std::ifstream file(ConfigFileLocation);
    json j;
    file >> j;

    /*if (parsingFailed)
    {
        std::cerr << "Error: Config File Found, but could not be parsed\n";
        std::cerr << "Config Filename: " << ConfigFileLocation << "\n";
        std::cerr << "The bot will not run without its configuration file\n";
        std::cerr << "Please check that the file exists, is not empty, and is valid JSON. Incomplete paths are relative to the bot .exe file\n";
        std::cerr << "You can change the config file location in Config::ConfigFile::ConfigFileLocation\n";
        ConfigFileParsed = false;
        return;
    }*/

    // Parse the Bot Info
    if (j.count("Bot Info") && j["Bot Info"].is_object())
    {
        const json & info = j["Bot Info"];
        JSONTools::ReadString("BotName", info, BotName);
        JSONTools::ReadString("Authors", info, Authors);
        JSONTools::ReadBool("PrintInfoOnStart", info, PrintInfoOnStart);
    }

    // Parse the Micro Options
    if (j.count("Micro") && j["Micro"].is_object())
    {
        const json & micro = j["Micro"];
        JSONTools::ReadBool("KiteWithRangedUnits", micro, KiteWithRangedUnits);
        JSONTools::ReadBool("ScoutHarassEnemy", micro, ScoutHarassEnemy);
    }

    // Parse the BWAPI Options
    if (j.count("BWAPI") && j["BWAPI"].is_object())
    {
        const json & bwapi = j["BWAPI"];
        JSONTools::ReadInt("SetLocalSpeed", bwapi, SetLocalSpeed);
        JSONTools::ReadInt("SetFrameSkip", bwapi, SetFrameSkip);
        JSONTools::ReadBool("UserInput", bwapi, UserInput);
        JSONTools::ReadBool("CompleteMapInformation", bwapi, CompleteMapInformation);
    }

    // Parse the Macro Options
    if (j.count("Macro") && j["Macro"].is_object())
    {
        const json & macro = j["Macro"];
        JSONTools::ReadInt("BuildingSpacing", macro, BuildingSpacing);
        JSONTools::ReadInt("PylongSpacing", macro, PylonSpacing);
        JSONTools::ReadInt("WorkersPerRefinery", macro, WorkersPerRefinery);
    }

    // Parse the Debug Options
    if (j.count("Debug") && j["Debug"].is_object())
    {
        const json & debug = j["Debug"];
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
    if (j.count("Modules") && j["Modules"].is_object())
    {
        const json & module = j["Modules"];

        JSONTools::ReadBool("UseAutoObserver", module, UsingAutoObserver);
    }
}
