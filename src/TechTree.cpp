#include "TechTree.h"
#include "Util.h"
#include "CCBot.h"

TechTree::TechTree(CCBot & bot)
    : m_bot(bot)
{

}

void TechTree::initUnitTypeData()
{
    // Protoss Buildings
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_PYLON] =                   { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_NEXUS] =                   { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR] =             { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE] =         { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY, sc2::UNIT_TYPEID::PROTOSS_WARPGATE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE] =              { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON] =             { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_STARGATE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_FORGE] =                   { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_NEXUS }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_GATEWAY] =                 { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_NEXUS }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_STARGATE] =                { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON] =            { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY] =             { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY] =        { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE] =          { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL] =         { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, false, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {} };

    // Protoss Units
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_PROBE] =                   { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_NEXUS }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_MOTHERSHIPCORE] =          { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_NEXUS }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ZEALOT] =                  { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_SENTRY] =                  { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY }, false, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_STALKER] =                 { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY }, false, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_HIGHTEMPLAR] =             { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY }, false, { sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_DARKTEMPLAR] =             { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY }, false, { sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ADEPT] =                   { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY }, false, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_COLOSSUS] =                { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY }, false, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_DISRUPTOR] =               { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY }, false, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_WARPPRISM] =               { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_OBSERVER] =                { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY }, false, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_IMMORTAL] =                { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY }, false, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_CARRIER] =                 { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_STARGATE }, false, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ORACLE] =                  { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_STARGATE }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_PHOENIX] =                 { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_STARGATE }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_VOIDRAY] =                 { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_STARGATE }, false, {}, {} };  
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_TEMPEST] =                 { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_STARGATE }, false, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_INTERCEPTOR] =             { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_CARRIER }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ORACLESTASISTRAP] =        { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_ORACLE }, false, {}, {} }; 

    // Terran Buildings
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER] =            { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT] =              { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };  
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_REFINERY] =                 { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_ARMORY] =                   { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_FACTORY, sc2::UNIT_TYPEID::TERRAN_FACTORYFLYING }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BARRACKS] =                 { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT, sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOTLOWERED }, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_SENSORTOWER] =              { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_FACTORY] =                  { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_BARRACKS, sc2::UNIT_TYPEID::TERRAN_BARRACKSFLYING }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_FUSIONCORE] =               { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_STARPORT, sc2::UNIT_TYPEID::TERRAN_STARPORTFLYING }, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_STARPORT] =                 { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_FACTORY, sc2::UNIT_TYPEID::TERRAN_FACTORYFLYING }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY] =             { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_BARRACKS, sc2::UNIT_TYPEID::TERRAN_BARRACKSFLYING }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BUNKER] =                   { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_BARRACKS, sc2::UNIT_TYPEID::TERRAN_BARRACKSFLYING }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY] =           { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER, sc2::UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING, sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS, sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND, sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING }, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_MISSILETURRET] =            { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND] =           { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS] =        { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER }, false, {}, {} };

    // Terran Addons
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BARRACKSREACTOR] =          { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_BARRACKS }, false, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB] =          { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_BARRACKS }, false, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_FACTORYREACTOR] =           { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, false, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB] =           { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, false, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_STARPORTREACTOR] =          { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, false, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB] =          { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, false, {}, {} };

    // Terran Units
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_SCV] =                      { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB] =          { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_BARRACKS }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_GHOST] =                    { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_BARRACKS }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_MARAUDER] =                 { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_BARRACKS }, true, { sc2::UNIT_TYPEID::TERRAN_TECHLAB, sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB, sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB, sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_MARINE] =                   { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_BARRACKS }, false, {}, {} };
	m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_REAPER] =                   { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_BARRACKS }, false, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_FACTORYREACTOR] =           { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB] =           { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_HELLION] =                  { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_HELLIONTANK] =              { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, false, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_CYCLONE] =                  { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, false, {}, {} };  
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_SIEGETANK] =                { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, true, { sc2::UNIT_TYPEID::TERRAN_TECHLAB, sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB, sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB, sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_THOR] =                     { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, false, {}, {} };  
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_WIDOWMINE] =                { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_NUKE] =                     { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_STARPORTREACTOR] =          { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB] =          { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BANSHEE] =                  { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, true, { sc2::UNIT_TYPEID::TERRAN_TECHLAB, sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB, sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB, sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BATTLECRUISER] =            { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_LIBERATOR] =                { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_VIKINGFIGHTER] =            { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_RAVEN] =                    { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, true, { sc2::UNIT_TYPEID::TERRAN_TECHLAB, sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB, sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB, sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_MEDIVAC] =                  { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, false, {}, {} }; 

    // Zerg Buildings
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_HATCHERY] =                   { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_EXTRACTOR] =                  { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL] =               { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_HATCHERY, sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER] =           { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_HATCHERY, sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_BANELINGNEST] =               { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN] =               { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT] =             { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_NYDUSCANAL] =                 { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_NYDUSNETWORK }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_NYDUSNETWORK] =               { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_ROACHWARREN] =                { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_SPINECRAWLER] =               { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_SPIRE] =                      { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_SPORECRAWLER] =               { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN] =            { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_DRONE }, false, { sc2::UNIT_TYPEID::ZERG_HIVE }, {} };

    // Zerg Units
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_OVERLORD] =                   { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_BANELING] =                   { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_BANELINGNEST }, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_CORRUPTOR] =                  { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_DRONE] =                      { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_HYDRALISK] =                  { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN, sc2::UNIT_TYPEID::ZERG_LURKERDENMP }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_INFESTOR] =                   { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_MUTALISK] =                   { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_QUEEN] =                      { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_ROACH] =                      { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_ROACHWARREN }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_SWARMHOSTMP] =                { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_ULTRALISK] =                  { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_VIPER] =                      { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_ZERGLING] =                   { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_LARVA }, false, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_LAIR] =                       { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_HATCHERY }, false, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_HIVE] =                       { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_LAIR }, false, {}, {} };  
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_GREATERSPIRE] =               { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_SPIRE }, false, {}, {} }; 
}

void TechTree::initUpgradeData()
{
    // Terran Upgrades
    m_upgradeData[sc2::UPGRADE_ID::BANSHEECLOAK] =                      { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::BANSHEESPEED] =                      { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::BATTLECRUISERENABLESPECIALIZATIONS]= { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::DRILLCLAWS] =                        { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::HIGHCAPACITYBARRELS] =               { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::HISECAUTOTRACKING] =                 { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::MAGFIELDLAUNCHERS] =                 { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::MEDIVACINCREASESPEEDBOOST] =         { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::NEOSTEELFRAME] =                     { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PERSONALCLOAKING] =                  { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PUNISHERGRENADES] =                  { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::RAVENCORVIDREACTOR] =                { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::RAVENRECALIBRATEDEXPLOSIVES] =       { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::STIMPACK] =                          { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANBUILDINGARMOR] =               { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL1] =        { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL2] =        { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, false, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL3] =        { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, false, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL1] =       { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL2] =       { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, false, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL3] =       { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, false, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::LIBERATORAGRANGEUPGRADE] =           { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL1] =           { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL2] =           { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, false, {}, {sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL3] =           { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, false, {}, {sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL1] =  { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL2] =  { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, false, {}, {sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL3] =  { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, false, {}, {sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL1] =        { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL2] =        { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, false, {}, {sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL3] =        { sc2::Race::Terran, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, false, {}, {sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL2} };

    // Protoss Upgrades
    m_upgradeData[sc2::UPGRADE_ID::ADEPTPIERCINGATTACK] =               { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::BLINKTECH] =                         { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::CARRIERLAUNCHSPEEDUPGRADE] =         { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::CHARGE] =                            { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::DARKTEMPLARBLINKUPGRADE] =           { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::EXTENDEDTHERMALLANCE] =              { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::GRAVITICDRIVE] =                     { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::OBSERVERGRAVITICBOOSTER] =           { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PHOENIXRANGEUPGRADE] =               { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL1] =            { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL2] =            { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, false, {}, {sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL3] =            { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, false, {}, {sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL1] =           { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL2] =           { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, false, {}, {sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL3] =           { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, false, {}, {sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL3} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL1] =         { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL2] =         { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, false, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, { sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL3] =         { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, false, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, { sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL2 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL1] =        { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL2] =        { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, false, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, { sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL3] =        { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, false, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, { sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL2 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL1] =              { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL2] =              { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, false, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, { sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL3] =              { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, false, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, { sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::PSISTORMTECH] =                      { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::WARPGATERESEARCH] =                  { sc2::Race::Protoss, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, false, {}, {} };

    // Zerg Upgrades
    m_upgradeData[sc2::UPGRADE_ID::BURROW] =                            { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_HATCHERY, sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::CENTRIFICALHOOKS] =                  { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_BANELINGNEST }, false, {}, {} }; 
    m_upgradeData[sc2::UPGRADE_ID::CHITINOUSPLATING] =                  { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::EVOLVEGROOVEDSPINES] =               { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::EVOLVEMUSCULARAUGMENTS] =            { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::GLIALRECONSTITUTION] =               { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_ROACHWARREN }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_upgradeData[sc2::UPGRADE_ID::INFESTORENERGYUPGRADE] =             { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::NEURALPARASITE] =                    { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::OVERLORDSPEED] =                     { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_HATCHERY, sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, false, {}, {} };                       
    m_upgradeData[sc2::UPGRADE_ID::TUNNELINGCLAWS] =                    { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_ROACHWARREN }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL1] =             { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL2] =             { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, { sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL3] =             { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, false, { sc2::UNIT_TYPEID::ZERG_HIVE }, { sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL2 } };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL1] =            { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL2] =            { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, { sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL3] =            { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, false, { sc2::UNIT_TYPEID::ZERG_HIVE }, { sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL2 } };
    m_upgradeData[sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL1] =            { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL2] =            { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL3] =            { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, false, { sc2::UNIT_TYPEID::ZERG_HIVE }, {sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGLINGATTACKSPEED] =               { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, false, { sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGLINGMOVEMENTSPEED] =             { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL1] =            { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL2] =            { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL3] =            { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, false, { sc2::UNIT_TYPEID::ZERG_HIVE }, {sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL1] =          { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, false, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL2] =          { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, false, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL3] =          { sc2::Race::Zerg, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, false, { sc2::UNIT_TYPEID::ZERG_HIVE }, {sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL2} };

    // Unknown
    
    m_upgradeData[sc2::UPGRADE_ID::SHIELDWALL] =                        { sc2::Race::Random, { sc2::UNIT_TYPEID::TERRAN_SCV }, false, {}, {} };
    
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