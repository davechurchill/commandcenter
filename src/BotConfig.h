#pragma once

#include "Common.h"

class BotConfig
{

public:

    bool ConfigFileFound;
    bool ConfigFileParsed;
    std::string ConfigFileLocation;
        
    bool UsingAutoObserver;		
    
    std::string BotName;
    std::string Authors;
    bool PrintInfoOnStart;
    std::string BotMode;

    int SetLocalSpeed;
    int SetFrameSkip;
    bool UserInput;
    bool CompleteMapInformation;
    
    std::string StrategyName;
    std::string ReadDir;
    std::string WriteDir;
    bool UseEnemySpecificStrategy;
    bool FoundEnemySpecificStrategy;
    
    bool DrawGameInfo;
    bool DrawTileInfo;
    bool DrawBaseLocationInfo;
    bool DrawWalkableSectors;
    bool DrawResourceInfo;
    bool DrawProductionInfo;
    bool DrawScoutInfo;
    bool DrawWorkerInfo;
    bool DrawModuleTimers;
    bool DrawReservedBuildingTiles;
    bool DrawBuildingInfo;
    bool DrawEnemyUnitInfo;
    bool DrawLastSeenTileInfo;
    bool DrawUnitTargetInfo;
    bool DrawSquadInfo;		
    
    CCColor ColorLineTarget;
    CCColor ColorLineMineral;
    CCColor ColorUnitNearEnemy;
    CCColor ColorUnitNotNearEnemy;
    
    bool KiteWithRangedUnits;    
    bool ScoutHarassEnemy;
    
    int WorkersPerRefinery;
    int BuildingSpacing;
    int PylonSpacing;
 
    BotConfig();

    void readConfigFile();
};