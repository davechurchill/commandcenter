#include "TechTree.h"
#include "Util.h"
#include "CCBot.h"
#include "BuildType.h"
#include "Timer.hpp"

TechTree::TechTree(CCBot & bot)
    : m_bot(bot)
{
    Timer t;
    t.start();

    initUnitTypeData();
    initUpgradeData();

    double ms = t.getElapsedTimeInMilliSec();
    std::cout << "Tech Tree constructed in " << ms << "ms\n";
}

void TechTree::initUnitTypeData()
{
    // Protoss Buildings
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_PYLON] =                   { sc2::Race::Protoss, sc2::ABILITY_ID::BUILD_PYLON, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_NEXUS] =                   { sc2::Race::Protoss, sc2::ABILITY_ID::BUILD_NEXUS, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR] =             { sc2::Race::Protoss, sc2::ABILITY_ID::BUILD_ASSIMILATOR, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE] =         { sc2::Race::Protoss, sc2::ABILITY_ID::BUILD_CYBERNETICSCORE, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY, sc2::UNIT_TYPEID::PROTOSS_WARPGATE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE] =              { sc2::Race::Protoss, sc2::ABILITY_ID::BUILD_DARKSHRINE, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON] =             { sc2::Race::Protoss, sc2::ABILITY_ID::BUILD_FLEETBEACON, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_STARGATE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_FORGE] =                   { sc2::Race::Protoss, sc2::ABILITY_ID::BUILD_FORGE, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_NEXUS }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_GATEWAY] =                 { sc2::Race::Protoss, sc2::ABILITY_ID::BUILD_GATEWAY, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_NEXUS }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_STARGATE] =                { sc2::Race::Protoss, sc2::ABILITY_ID::BUILD_STARGATE, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON] =            { sc2::Race::Protoss, sc2::ABILITY_ID::BUILD_PHOTONCANNON, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY] =             { sc2::Race::Protoss, sc2::ABILITY_ID::BUILD_ROBOTICSBAY, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY] =        { sc2::Race::Protoss, sc2::ABILITY_ID::BUILD_ROBOTICSFACILITY, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE] =          { sc2::Race::Protoss, sc2::ABILITY_ID::BUILD_TEMPLARARCHIVE, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL] =         { sc2::Race::Protoss, sc2::ABILITY_ID::BUILD_TWILIGHTCOUNCIL, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {} };

    // Protoss Units
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_PROBE] =                   { sc2::Race::Protoss, sc2::ABILITY_ID::TRAIN_PROBE, { sc2::UNIT_TYPEID::PROTOSS_NEXUS }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_MOTHERSHIPCORE] =          { sc2::Race::Protoss, sc2::ABILITY_ID::TRAIN_MOTHERSHIPCORE, { sc2::UNIT_TYPEID::PROTOSS_NEXUS }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ZEALOT] =                  { sc2::Race::Protoss, sc2::ABILITY_ID::TRAIN_ZEALOT, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_SENTRY] =                  { sc2::Race::Protoss, sc2::ABILITY_ID::TRAIN_SENTRY, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY }, false, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_STALKER] =                 { sc2::Race::Protoss, sc2::ABILITY_ID::TRAIN_STALKER, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY }, false, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_HIGHTEMPLAR] =             { sc2::Race::Protoss, sc2::ABILITY_ID::TRAIN_HIGHTEMPLAR, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY }, false, { sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_DARKTEMPLAR] =             { sc2::Race::Protoss, sc2::ABILITY_ID::TRAIN_DARKTEMPLAR, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY }, false, { sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ADEPT] =                   { sc2::Race::Protoss, sc2::ABILITY_ID::TRAIN_ADEPT, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY }, false, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_COLOSSUS] =                { sc2::Race::Protoss, sc2::ABILITY_ID::TRAIN_COLOSSUS,  { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY }, false, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_DISRUPTOR] =               { sc2::Race::Protoss, sc2::ABILITY_ID::TRAIN_DISRUPTOR, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY }, false, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_WARPPRISM] =               { sc2::Race::Protoss, sc2::ABILITY_ID::TRAIN_WARPPRISM, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_OBSERVER] =                { sc2::Race::Protoss, sc2::ABILITY_ID::TRAIN_OBSERVER, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY }, false, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_IMMORTAL] =                { sc2::Race::Protoss, sc2::ABILITY_ID::TRAIN_IMMORTAL, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY }, false, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_CARRIER] =                 { sc2::Race::Protoss, sc2::ABILITY_ID::TRAIN_CARRIER, { sc2::UNIT_TYPEID::PROTOSS_STARGATE }, false, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ORACLE] =                  { sc2::Race::Protoss, sc2::ABILITY_ID::TRAIN_ORACLE, { sc2::UNIT_TYPEID::PROTOSS_STARGATE }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_PHOENIX] =                 { sc2::Race::Protoss, sc2::ABILITY_ID::TRAIN_PHOENIX, { sc2::UNIT_TYPEID::PROTOSS_STARGATE }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_VOIDRAY] =                 { sc2::Race::Protoss, sc2::ABILITY_ID::TRAIN_VOIDRAY, { sc2::UNIT_TYPEID::PROTOSS_STARGATE }, false, {}, {} };  
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_TEMPEST] =                 { sc2::Race::Protoss, sc2::ABILITY_ID::TRAIN_TEMPEST, { sc2::UNIT_TYPEID::PROTOSS_STARGATE }, false, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_INTERCEPTOR] =             { sc2::Race::Protoss, sc2::ABILITY_ID::BUILD_INTERCEPTORS, { sc2::UNIT_TYPEID::PROTOSS_CARRIER }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ORACLESTASISTRAP] =        { sc2::Race::Protoss, sc2::ABILITY_ID::BUILD_STASISTRAP, { sc2::UNIT_TYPEID::PROTOSS_ORACLE }, false, {}, {} }; 

    // Terran Buildings
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER] =            { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_COMMANDCENTER, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT] =              { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_SUPPLYDEPOT, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };  
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_REFINERY] =                 { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_REFINERY, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_ARMORY] =                   { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_ARMORY, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_FACTORY, sc2::UNIT_TYPEID::TERRAN_FACTORYFLYING }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BARRACKS] =                 { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_BARRACKS, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT, sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOTLOWERED }, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_SENSORTOWER] =              { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_SENSORTOWER, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_FACTORY] =                  { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_FACTORY, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_BARRACKS, sc2::UNIT_TYPEID::TERRAN_BARRACKSFLYING }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_FUSIONCORE] =               { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_FUSIONCORE, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_STARPORT, sc2::UNIT_TYPEID::TERRAN_STARPORTFLYING }, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_STARPORT] =                 { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_STARPORT, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_FACTORY, sc2::UNIT_TYPEID::TERRAN_FACTORYFLYING }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY] =             { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_GHOSTACADEMY, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_BARRACKS, sc2::UNIT_TYPEID::TERRAN_BARRACKSFLYING }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BUNKER] =                   { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_BUNKER, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_BARRACKS, sc2::UNIT_TYPEID::TERRAN_BARRACKSFLYING }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY] =           { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_ENGINEERINGBAY, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER, sc2::UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING, sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS, sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND, sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING }, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_MISSILETURRET] =            { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_MISSILETURRET, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND] =           { sc2::Race::Terran, sc2::ABILITY_ID::MORPH_ORBITALCOMMAND, { sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS] =        { sc2::Race::Terran, sc2::ABILITY_ID::MORPH_PLANETARYFORTRESS, { sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER }, false, {}, {} };

    // Terran Addons
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BARRACKSREACTOR] =          { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_REACTOR_BARRACKS, { sc2::UNIT_TYPEID::TERRAN_BARRACKS }, false, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB] =          { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_TECHLAB_BARRACKS, { sc2::UNIT_TYPEID::TERRAN_BARRACKS }, false, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_FACTORYREACTOR] =           { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_REACTOR_FACTORY, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, false, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB] =           { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_TECHLAB_FACTORY, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, false, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_STARPORTREACTOR] =          { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_REACTOR_STARPORT, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, false, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB] =          { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_TECHLAB_STARPORT, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, false, {}, {} };

    // Terran Units
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_SCV] =                      { sc2::Race::Terran, sc2::ABILITY_ID::TRAIN_SCV, { sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_GHOST] =                    { sc2::Race::Terran, sc2::ABILITY_ID::TRAIN_GHOST, { sc2::UNIT_TYPEID::TERRAN_BARRACKS }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_MARAUDER] =                 { sc2::Race::Terran, sc2::ABILITY_ID::TRAIN_MARAUDER, { sc2::UNIT_TYPEID::TERRAN_BARRACKS }, true, { sc2::UNIT_TYPEID::TERRAN_TECHLAB, sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB, sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB, sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_MARINE] =                   { sc2::Race::Terran, sc2::ABILITY_ID::TRAIN_MARINE, { sc2::UNIT_TYPEID::TERRAN_BARRACKS }, false, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_REAPER] =                   { sc2::Race::Terran, sc2::ABILITY_ID::TRAIN_REAPER, { sc2::UNIT_TYPEID::TERRAN_BARRACKS }, false, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_HELLION] =                  { sc2::Race::Terran, sc2::ABILITY_ID::TRAIN_HELLION, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, false, {}, {} }; 
    //m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_HELLIONTANK] =              { sc2::Race::Terran, sc2::ABILITY_ID::HELL, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, false, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_CYCLONE] =                  { sc2::Race::Terran, sc2::ABILITY_ID::TRAIN_CYCLONE, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, false, {}, {} };  
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_SIEGETANK] =                { sc2::Race::Terran, sc2::ABILITY_ID::TRAIN_SIEGETANK, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, true, { sc2::UNIT_TYPEID::TERRAN_TECHLAB, sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB, sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB, sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_THOR] =                     { sc2::Race::Terran, sc2::ABILITY_ID::TRAIN_THOR, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, false, {}, {} };  
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_WIDOWMINE] =                { sc2::Race::Terran, sc2::ABILITY_ID::TRAIN_WIDOWMINE, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_NUKE] =                     { sc2::Race::Terran, sc2::ABILITY_ID::BUILD_NUKE, { sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BANSHEE] =                  { sc2::Race::Terran, sc2::ABILITY_ID::TRAIN_BANSHEE, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, true, { sc2::UNIT_TYPEID::TERRAN_TECHLAB, sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB, sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB, sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BATTLECRUISER] =            { sc2::Race::Terran, sc2::ABILITY_ID::TRAIN_BATTLECRUISER, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_LIBERATOR] =                { sc2::Race::Terran, sc2::ABILITY_ID::TRAIN_LIBERATOR, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_VIKINGFIGHTER] =            { sc2::Race::Terran, sc2::ABILITY_ID::TRAIN_VIKINGFIGHTER, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_RAVEN] =                    { sc2::Race::Terran, sc2::ABILITY_ID::TRAIN_RAVEN, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, true, { sc2::UNIT_TYPEID::TERRAN_TECHLAB, sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB, sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB, sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_MEDIVAC] =                  { sc2::Race::Terran, sc2::ABILITY_ID::TRAIN_MEDIVAC, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, false, {}, {} }; 

    // Zerg Buildings
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_HATCHERY] =                   { sc2::Race::Zerg, sc2::ABILITY_ID::BUILD_HATCHERY, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_EXTRACTOR] =                  { sc2::Race::Zerg, sc2::ABILITY_ID::BUILD_EXTRACTOR, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL] =               { sc2::Race::Zerg, sc2::ABILITY_ID::BUILD_SPAWNINGPOOL, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_HATCHERY, sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER] =           { sc2::Race::Zerg, sc2::ABILITY_ID::BUILD_EVOLUTIONCHAMBER, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_HATCHERY, sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_BANELINGNEST] =               { sc2::Race::Zerg, sc2::ABILITY_ID::BUILD_BANELINGNEST, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN] =               { sc2::Race::Zerg, sc2::ABILITY_ID::BUILD_HYDRALISKDEN, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT] =             { sc2::Race::Zerg, sc2::ABILITY_ID::BUILD_INFESTATIONPIT, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_NYDUSCANAL] =                 { sc2::Race::Zerg, sc2::ABILITY_ID::BUILD_NYDUSWORM, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_NYDUSNETWORK }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_NYDUSNETWORK] =               { sc2::Race::Zerg, sc2::ABILITY_ID::BUILD_NYDUSNETWORK, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_ROACHWARREN] =                { sc2::Race::Zerg, sc2::ABILITY_ID::BUILD_ROACHWARREN, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_SPINECRAWLER] =               { sc2::Race::Zerg, sc2::ABILITY_ID::BUILD_SPINECRAWLER, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_SPIRE] =                      { sc2::Race::Zerg, sc2::ABILITY_ID::BUILD_SPIRE, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_GREATERSPIRE] =               { sc2::Race::Zerg, sc2::ABILITY_ID::MORPH_GREATERSPIRE, { sc2::UNIT_TYPEID::ZERG_SPIRE }, false, { sc2::UNIT_TYPEID::ZERG_HIVE }, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_SPORECRAWLER] =               { sc2::Race::Zerg, sc2::ABILITY_ID::BUILD_SPORECRAWLER, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN] =            { sc2::Race::Zerg, sc2::ABILITY_ID::BUILD_ULTRALISKCAVERN, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_LAIR] =                       { sc2::Race::Zerg, sc2::ABILITY_ID::MORPH_LAIR, { sc2::UNIT_TYPEID::ZERG_HATCHERY }, false, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_HIVE] =                       { sc2::Race::Zerg, sc2::ABILITY_ID::MORPH_HIVE, { sc2::UNIT_TYPEID::ZERG_LAIR }, false, {}, {} };  

    // Zerg Units
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_OVERLORD] =                   { sc2::Race::Zerg, sc2::ABILITY_ID::TRAIN_OVERLORD, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_BANELING] =                   { sc2::Race::Zerg, sc2::ABILITY_ID::TRAIN_BANELING, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_BANELINGNEST }, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_CORRUPTOR] =                  { sc2::Race::Zerg, sc2::ABILITY_ID::TRAIN_CORRUPTOR, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_DRONE] =                      { sc2::Race::Zerg, sc2::ABILITY_ID::TRAIN_DRONE, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_HYDRALISK] =                  { sc2::Race::Zerg, sc2::ABILITY_ID::TRAIN_HYDRALISK, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN, sc2::UNIT_TYPEID::ZERG_LURKERDENMP }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_INFESTOR] =                   { sc2::Race::Zerg, sc2::ABILITY_ID::TRAIN_INFESTOR, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_MUTALISK] =                   { sc2::Race::Zerg, sc2::ABILITY_ID::TRAIN_MUTALISK, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_ROACH] =                      { sc2::Race::Zerg, sc2::ABILITY_ID::TRAIN_ROACH, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_ROACHWARREN }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_SWARMHOSTMP] =                { sc2::Race::Zerg, sc2::ABILITY_ID::TRAIN_SWARMHOST, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_ULTRALISK] =                  { sc2::Race::Zerg, sc2::ABILITY_ID::TRAIN_ULTRALISK, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_VIPER] =                      { sc2::Race::Zerg, sc2::ABILITY_ID::TRAIN_VIPER, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_ZERGLING] =                   { sc2::Race::Zerg, sc2::ABILITY_ID::TRAIN_ZERGLING, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_QUEEN] =                      { sc2::Race::Zerg, sc2::ABILITY_ID::TRAIN_QUEEN, { sc2::UNIT_TYPEID::ZERG_HATCHERY }, false, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, {} };
}

void TechTree::initUpgradeData()
{
    // Terran Upgrades
    m_upgradeData[sc2::UPGRADE_ID::BANSHEECLOAK] =                      { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_BANSHEECLOAKINGFIELD, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::BANSHEESPEED] =                      { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_BANSHEEHYPERFLIGHTROTORS, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::BATTLECRUISERENABLESPECIALIZATIONS]= { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_BATTLECRUISERWEAPONREFIT, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::DRILLCLAWS] =                        { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_DRILLINGCLAWS, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::HIGHCAPACITYBARRELS] =               { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_HIGHCAPACITYFUELTANKS, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::HISECAUTOTRACKING] =                 { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_HISECAUTOTRACKING, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::LIBERATORAGRANGEUPGRADE] =           { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_ADVANCEDBALLISTICS, { sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::MAGFIELDLAUNCHERS] =                 { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_MAGFIELDLAUNCHERS, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::MEDIVACINCREASESPEEDBOOST] =         { sc2::Race::Terran, sc2::ABILITY_ID::EFFECT_MEDIVACIGNITEAFTERBURNERS, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::NEOSTEELFRAME] =                     { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_NEOSTEELFRAME, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PERSONALCLOAKING] =                  { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_PERSONALCLOAKING, { sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PUNISHERGRENADES] =                  { sc2::Race::Terran, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::RAVENCORVIDREACTOR] =                { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_RAVENCORVIDREACTOR, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::RAVENRECALIBRATEDEXPLOSIVES] =       { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_RAVENRECALIBRATEDEXPLOSIVES, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::SHIELDWALL] =                        { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_COMBATSHIELD, { sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::STIMPACK] =                          { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_STIMPACK, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANBUILDINGARMOR] =               { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_TERRANSTRUCTUREARMORUPGRADE, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL1] =        { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL1, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL2] =        { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL2, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, false, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL3] =        { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL3, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, false, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL1] =       { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL1, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL2] =       { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL2, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, false, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL3] =       { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL3, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, false, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL1] =           { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL1, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL2] =           { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL2, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, false, {}, {sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL3] =           { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL3, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, false, {}, {sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL1] =  { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL1, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL2] =  { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL2, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, false, {}, {sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL3] =  { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL3, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, false, {}, {sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL1] =        { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL1, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL2] =        { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL2, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, false, {}, {sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL3] =        { sc2::Race::Terran, sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL3, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, false, {}, {sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL2} };

    // Protoss Upgrades
    m_upgradeData[sc2::UPGRADE_ID::ADEPTPIERCINGATTACK] =               { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_ADEPTRESONATINGGLAIVES, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::BLINKTECH] =                         { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_BLINK, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::CARRIERLAUNCHSPEEDUPGRADE] =         { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_INTERCEPTORGRAVITONCATAPULT, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::CHARGE] =                            { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_CHARGE, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::DARKTEMPLARBLINKUPGRADE] =           { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_SHADOWSTRIKE, { sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::EXTENDEDTHERMALLANCE] =              { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_EXTENDEDTHERMALLANCE, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::GRAVITICDRIVE] =                     { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_GRAVITICDRIVE, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::OBSERVERGRAVITICBOOSTER] =           { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_GRAVITICBOOSTER, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PHOENIXRANGEUPGRADE] =               { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_PHOENIXANIONPULSECRYSTALS, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL1] =            { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL1,   { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL2] =            { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL2,   { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, false, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, {sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL3] =            { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL3,   { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, false, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, {sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL1] =           { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL1, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL2] =           { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL2, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, false, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, {sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL3] =           { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL3, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, false, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, {sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL3} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL1] =         { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL1, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL2] =         { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL2, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, false, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, { sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL3] =         { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL3, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, false, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, { sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL2 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL1] =        { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL1, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL2] =        { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL2, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, false, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, { sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL3] =        { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL3, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, false, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, { sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL2 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL1] =              { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL1, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL2] =              { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL2, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, false, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, { sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL3] =              { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL3, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, false, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, { sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::PSISTORMTECH] =                      { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_PSISTORM, { sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::WARPGATERESEARCH] =                  { sc2::Race::Protoss, sc2::ABILITY_ID::RESEARCH_WARPGATE, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, false, {}, {} };

    // Zerg Upgrades
    m_upgradeData[sc2::UPGRADE_ID::BURROW] =                            { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_BURROW, { sc2::UNIT_TYPEID::ZERG_HATCHERY, sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::CENTRIFICALHOOKS] =                  { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_CENTRIFUGALHOOKS, { sc2::UNIT_TYPEID::ZERG_BANELINGNEST }, false, {}, {} }; 
    m_upgradeData[sc2::UPGRADE_ID::CHITINOUSPLATING] =                  { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_CHITINOUSPLATING, { sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::EVOLVEGROOVEDSPINES] =               { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_GROOVEDSPINES, { sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::EVOLVEMUSCULARAUGMENTS] =            { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_MUSCULARAUGMENTS, { sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::GLIALRECONSTITUTION] =               { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_GLIALREGENERATION, { sc2::UNIT_TYPEID::ZERG_ROACHWARREN }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_upgradeData[sc2::UPGRADE_ID::INFESTORENERGYUPGRADE] =             { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_PATHOGENGLANDS, { sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::NEURALPARASITE] =                    { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_NEURALPARASITE, { sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::OVERLORDSPEED] =                     { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_PNEUMATIZEDCARAPACE, { sc2::UNIT_TYPEID::ZERG_HATCHERY, sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, false, {}, {} };                       
    m_upgradeData[sc2::UPGRADE_ID::TUNNELINGCLAWS] =                    { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_TUNNELINGCLAWS, { sc2::UNIT_TYPEID::ZERG_ROACHWARREN }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL1] =             { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_ZERGFLYERARMORLEVEL1, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL2] =             { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_ZERGFLYERARMORLEVEL2, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, { sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL3] =             { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_ZERGFLYERARMORLEVEL3, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, false, { sc2::UNIT_TYPEID::ZERG_HIVE }, { sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL2 } };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL1] =            { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_ZERGFLYERATTACKLEVEL1, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL2] =            { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_ZERGFLYERATTACKLEVEL2, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, { sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL3] =            { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_ZERGFLYERATTACKLEVEL3, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, false, { sc2::UNIT_TYPEID::ZERG_HIVE }, { sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL2 } };
    m_upgradeData[sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL1] =            { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_ZERGGROUNDARMORLEVEL1, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL2] =            { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_ZERGGROUNDARMORLEVEL2, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL3] =            { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_ZERGGROUNDARMORLEVEL3, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, false, { sc2::UNIT_TYPEID::ZERG_HIVE }, {sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGLINGATTACKSPEED] =               { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_ZERGLINGADRENALGLANDS, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, false, { sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGLINGMOVEMENTSPEED] =             { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_ZERGLINGMETABOLICBOOST, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL1] =            { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL1, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL2] =            { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL2, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL3] =            { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL3, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, false, { sc2::UNIT_TYPEID::ZERG_HIVE }, {sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL1] =          { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONSLEVEL1, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL2] =          { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONSLEVEL2, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL3] =          { sc2::Race::Zerg, sc2::ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONSLEVEL3, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, false, { sc2::UNIT_TYPEID::ZERG_HIVE }, {sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL2} };

    // Unknown
    
    
    
}

const std::vector<sc2::UnitTypeID> & TechTree::getWhatBuilds(const sc2::UnitTypeID & type) const
{
    return m_unitTypeData.at(type).m_whatBuilds;
}

const std::vector<sc2::UnitTypeID> & TechTree::getRequiredUnits(const sc2::UnitTypeID & type) const
{
    return m_unitTypeData.at(type).m_requiredUnits;
}

const std::vector<sc2::UpgradeID> &  TechTree::getRequiredUpgrades(const sc2::UnitTypeID & type) const
{
    return m_unitTypeData.at(type).m_requiredUpgrades;
}

const std::vector<sc2::UnitTypeID> & TechTree::getWhatBuilds(const sc2::UpgradeID & type) const
{
    return m_upgradeData.at(type).m_whatBuilds;
}

const std::vector<sc2::UnitTypeID> & TechTree::getRequiredUnits(const sc2::UpgradeID & type) const
{
    return m_upgradeData.at(type).m_requiredUnits;
}

const std::vector<sc2::UpgradeID> &  TechTree::getRequiredUpgrades(const sc2::UpgradeID & type) const
{
    return m_upgradeData.at(type).m_requiredUpgrades;
}

const std::vector<sc2::UnitTypeID> & TechTree::getWhatBuilds(const BuildType & type) const
{
    if (type.getBuildType() == BuildTypes::Unit)
    {
        return getWhatBuilds(type.getUnitTypeID());
    }
    else if (type.getBuildType() == BuildTypes::Upgrade)
    {
        return getWhatBuilds(type.getUpgradeID());
    }
    
    BOT_ASSERT(false, "Can't getWhatBuilds this type: %s", type.getName());

    return getWhatBuilds(type.getUnitTypeID());
}

const std::vector<sc2::UnitTypeID> & TechTree::getRequiredUnits(const BuildType & type) const
{
    if (type.getBuildType() == BuildTypes::Unit)
    {
        return getRequiredUnits(type.getUnitTypeID());
    }
    else if (type.getBuildType() == BuildTypes::Upgrade)
    {
        return getRequiredUnits(type.getUpgradeID());
    }
    
    BOT_ASSERT(false, "Can't getRequiredUnits this type: %s", type.getName());

    return getRequiredUnits(type.getUnitTypeID());
}

const std::vector<sc2::UpgradeID> &  TechTree::getRequiredUpgrades(const BuildType & type) const
{
        if (type.getBuildType() == BuildTypes::Unit)
    {
        return getRequiredUpgrades(type.getUnitTypeID());
    }
    else if (type.getBuildType() == BuildTypes::Upgrade)
    {
        return getRequiredUpgrades(type.getUpgradeID());
    }
    
    BOT_ASSERT(false, "Can't getRequiredUpgrades this type: %s", type.getName());

    return getRequiredUpgrades(type.getUnitTypeID());
}