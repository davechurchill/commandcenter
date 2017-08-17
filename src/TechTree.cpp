#include "TechTree.h"
#include "Util.h"
#include "CCBot.h"
#include "BuildType.h"
#include "Timer.hpp"

TechTree::TechTree(CCBot & bot)
    : m_bot(bot)
{

}

void TechTree::onStart()
{
    initUnitTypeData();
    initUpgradeData();
}

void TechTree::initUnitTypeData()
{
    m_upgradeData[0] = TypeData();

    // Protoss Buildings                                                                                  unit  bld   wrk    rfn    sup    hall   add
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_PYLON] =                   { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false,  true, false, false, sc2::ABILITY_ID::BUILD_PYLON, 0, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_NEXUS] =                   { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false,  true, false, sc2::ABILITY_ID::BUILD_NEXUS, 0, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR] =             { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false,  true, false, false, false, sc2::ABILITY_ID::BUILD_ASSIMILATOR, 0, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE] =         { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_CYBERNETICSCORE, 0, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY, sc2::UNIT_TYPEID::PROTOSS_WARPGATE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE] =              { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_DARKSHRINE, 0, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON] =             { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_FLEETBEACON, 0, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, { sc2::UNIT_TYPEID::PROTOSS_STARGATE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_FORGE] =                   { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_FORGE, 0, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, { sc2::UNIT_TYPEID::PROTOSS_NEXUS }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_GATEWAY] =                 { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_GATEWAY, 0, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, { sc2::UNIT_TYPEID::PROTOSS_NEXUS }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_STARGATE] =                { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_STARGATE, 0, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON] =            { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_PHOTONCANNON, 0, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY] =             { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_ROBOTICSBAY, 0, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY] =        { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_ROBOTICSFACILITY, 0, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE] =          { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_TEMPLARARCHIVE, 0, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL] =         { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_TWILIGHTCOUNCIL, 0, { sc2::UNIT_TYPEID::PROTOSS_PROBE }, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_WARPGATE] =                { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::MORPH_WARPGATE, 0, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY }, {}, { sc2::UPGRADE_ID::WARPGATERESEARCH } }; 

    // Protoss Units                                                                                      unit  bld   wrk    rfn    sup    hall   add
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_PROBE] =                   { sc2::Race::Protoss, 0, 0, 1, 0, true, false,  true, false, false, false, false, sc2::ABILITY_ID::TRAIN_PROBE, 0, { sc2::UNIT_TYPEID::PROTOSS_NEXUS }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_MOTHERSHIPCORE] =          { sc2::Race::Protoss, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_MOTHERSHIPCORE, 0, { sc2::UNIT_TYPEID::PROTOSS_NEXUS }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ZEALOT] =                  { sc2::Race::Protoss, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_ZEALOT, sc2::ABILITY_ID::TRAINWARP_ZEALOT, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_SENTRY] =                  { sc2::Race::Protoss, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_SENTRY, sc2::ABILITY_ID::TRAINWARP_SENTRY, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY }, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_STALKER] =                 { sc2::Race::Protoss, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_STALKER, sc2::ABILITY_ID::TRAINWARP_STALKER, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY }, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_HIGHTEMPLAR] =             { sc2::Race::Protoss, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_HIGHTEMPLAR, sc2::ABILITY_ID::TRAINWARP_HIGHTEMPLAR, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY }, { sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_DARKTEMPLAR] =             { sc2::Race::Protoss, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_DARKTEMPLAR, sc2::ABILITY_ID::TRAINWARP_DARKTEMPLAR, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY }, { sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ADEPT] =                   { sc2::Race::Protoss, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_ADEPT, sc2::ABILITY_ID::TRAINWARP_ADEPT, { sc2::UNIT_TYPEID::PROTOSS_GATEWAY }, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_COLOSSUS] =                { sc2::Race::Protoss, 0, 0, 6, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_COLOSSUS,  0, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY }, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_DISRUPTOR] =               { sc2::Race::Protoss, 0, 0, 3, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_DISRUPTOR, 0, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY }, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_WARPPRISM] =               { sc2::Race::Protoss, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_WARPPRISM, 0, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_OBSERVER] =                { sc2::Race::Protoss, 0, 0, 1, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_OBSERVER, 0, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY }, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_IMMORTAL] =                { sc2::Race::Protoss, 0, 0, 4, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_IMMORTAL, 0, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY }, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_CARRIER] =                 { sc2::Race::Protoss, 0, 0, 6, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_CARRIER, 0, { sc2::UNIT_TYPEID::PROTOSS_STARGATE }, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ORACLE] =                  { sc2::Race::Protoss, 0, 0, 3, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_ORACLE, 0, { sc2::UNIT_TYPEID::PROTOSS_STARGATE }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_PHOENIX] =                 { sc2::Race::Protoss, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_PHOENIX, 0, { sc2::UNIT_TYPEID::PROTOSS_STARGATE }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_VOIDRAY] =                 { sc2::Race::Protoss, 0, 0, 4, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_VOIDRAY, 0, { sc2::UNIT_TYPEID::PROTOSS_STARGATE }, {}, {} };  
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_TEMPEST] =                 { sc2::Race::Protoss, 0, 0, 4, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_TEMPEST, 0, { sc2::UNIT_TYPEID::PROTOSS_STARGATE }, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_INTERCEPTOR] =             { sc2::Race::Protoss, 0, 0, 0, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::BUILD_INTERCEPTORS, 0, { sc2::UNIT_TYPEID::PROTOSS_CARRIER }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::PROTOSS_ORACLESTASISTRAP] =        { sc2::Race::Protoss, 0, 0, 0, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::BUILD_STASISTRAP, 0, { sc2::UNIT_TYPEID::PROTOSS_ORACLE }, {}, {} }; 

    // Terran Buildings                                                                      m  g  s  t  unit  bld   wrk    rfn    sup    hall   add
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER] =            { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false,  true, false, sc2::ABILITY_ID::BUILD_COMMANDCENTER, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT] =              { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false,  true, false, false, sc2::ABILITY_ID::BUILD_SUPPLYDEPOT, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, {}, {} };  
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_REFINERY] =                 { sc2::Race::Terran, 0, 0, 0, 0, true, true, false,  true, false, false, false, sc2::ABILITY_ID::BUILD_REFINERY, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_ARMORY] =                   { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_ARMORY, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, { sc2::UNIT_TYPEID::TERRAN_FACTORY, sc2::UNIT_TYPEID::TERRAN_FACTORYFLYING }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BARRACKS] =                 { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_BARRACKS, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, { sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT, sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOTLOWERED }, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_SENSORTOWER] =              { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_SENSORTOWER, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_FACTORY] =                  { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_FACTORY, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, { sc2::UNIT_TYPEID::TERRAN_BARRACKS, sc2::UNIT_TYPEID::TERRAN_BARRACKSFLYING }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_FUSIONCORE] =               { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_FUSIONCORE, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, { sc2::UNIT_TYPEID::TERRAN_STARPORT, sc2::UNIT_TYPEID::TERRAN_STARPORTFLYING }, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_STARPORT] =                 { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_STARPORT, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, { sc2::UNIT_TYPEID::TERRAN_FACTORY, sc2::UNIT_TYPEID::TERRAN_FACTORYFLYING }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY] =             { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_GHOSTACADEMY, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, { sc2::UNIT_TYPEID::TERRAN_BARRACKS, sc2::UNIT_TYPEID::TERRAN_BARRACKSFLYING }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BUNKER] =                   { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_BUNKER, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, { sc2::UNIT_TYPEID::TERRAN_BARRACKS, sc2::UNIT_TYPEID::TERRAN_BARRACKSFLYING }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY] =           { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_ENGINEERINGBAY, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, { sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER, sc2::UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING, sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS, sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND, sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING }, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_MISSILETURRET] =            { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_MISSILETURRET, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND] =           { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::MORPH_ORBITALCOMMAND, 0, { sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS] =        { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::MORPH_PLANETARYFORTRESS, 0, { sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER }, {}, {} };

    // Terran Addons                                                                         m  g  s  t  unit  bld   wrk    rfn    sup    hall   add
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BARRACKSREACTOR] =          { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, true, sc2::ABILITY_ID::BUILD_REACTOR_BARRACKS, 0, { sc2::UNIT_TYPEID::TERRAN_BARRACKS }, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB] =          { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, true, sc2::ABILITY_ID::BUILD_TECHLAB_BARRACKS, 0, { sc2::UNIT_TYPEID::TERRAN_BARRACKS }, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_FACTORYREACTOR] =           { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, true, sc2::ABILITY_ID::BUILD_REACTOR_FACTORY, 0, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB] =           { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, true, sc2::ABILITY_ID::BUILD_TECHLAB_FACTORY, 0, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_STARPORTREACTOR] =          { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, true, sc2::ABILITY_ID::BUILD_REACTOR_STARPORT, 0, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB] =          { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, true, sc2::ABILITY_ID::BUILD_TECHLAB_STARPORT, 0, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, {}, {} };

    // Terran Equivalent Buildings
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOTLOWERED] =       m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT];
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BARRACKSFLYING] =           m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BARRACKS];
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING] =      m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER];
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_FACTORYFLYING] =            m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_FACTORY];
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING] =     m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND];
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_STARPORTFLYING] =           m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_STARPORT];

    // Terran Units                                                                          m  g  s  t  unit  bld    wrk    rfn    sup    hall   add
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_SCV] =                      { sc2::Race::Terran, 0, 0, 1, 0, true, false,  true, false, false, false, false, sc2::ABILITY_ID::TRAIN_SCV, 0, { sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_GHOST] =                    { sc2::Race::Terran, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_GHOST, 0, { sc2::UNIT_TYPEID::TERRAN_BARRACKS }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_MARAUDER] =                 { sc2::Race::Terran, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_MARAUDER, 0, { sc2::UNIT_TYPEID::TERRAN_BARRACKS }, { sc2::UNIT_TYPEID::TERRAN_TECHLAB, sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB, sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB, sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_MARINE] =                   { sc2::Race::Terran, 0, 0, 1, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_MARINE, 0, { sc2::UNIT_TYPEID::TERRAN_BARRACKS }, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_REAPER] =                   { sc2::Race::Terran, 0, 0, 1, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_REAPER, 0, { sc2::UNIT_TYPEID::TERRAN_BARRACKS }, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_HELLION] =                  { sc2::Race::Terran, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_HELLION, 0, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_CYCLONE] =                  { sc2::Race::Terran, 0, 0, 3, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_CYCLONE, 0, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, {}, {} };  
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_SIEGETANK] =                { sc2::Race::Terran, 0, 0, 3, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_SIEGETANK, 0, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, { sc2::UNIT_TYPEID::TERRAN_TECHLAB, sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB, sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB, sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_THOR] =                     { sc2::Race::Terran, 0, 0, 6, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_THOR, 0, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, {}, {} };  
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_WIDOWMINE] =                { sc2::Race::Terran, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_WIDOWMINE, 0, { sc2::UNIT_TYPEID::TERRAN_FACTORY }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_NUKE] =                     { sc2::Race::Terran, 0, 0, 0, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::BUILD_NUKE, 0, { sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BANSHEE] =                  { sc2::Race::Terran, 0, 0, 3, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_BANSHEE, 0, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, { sc2::UNIT_TYPEID::TERRAN_TECHLAB, sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB, sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB, sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_BATTLECRUISER] =            { sc2::Race::Terran, 0, 0, 6, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_BATTLECRUISER, 0, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_LIBERATOR] =                { sc2::Race::Terran, 0, 0, 3, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_LIBERATOR, 0, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_VIKINGFIGHTER] =            { sc2::Race::Terran, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_VIKINGFIGHTER, 0, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_RAVEN] =                    { sc2::Race::Terran, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_RAVEN, 0, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, { sc2::UNIT_TYPEID::TERRAN_TECHLAB, sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB, sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB, sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_MEDIVAC] =                  { sc2::Race::Terran, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_MEDIVAC, 0, { sc2::UNIT_TYPEID::TERRAN_STARPORT }, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::TERRAN_MULE] =                     { sc2::Race::Terran, 0, 0, 0, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::EFFECT_CALLDOWNMULE, 0, { sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND }, {}, {} }; 

    // Zerg Buildings                                                                      m  g  s  t  unit  bld   wrk    rfn    sup    hall   add
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_HATCHERY] =                   { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false,  true, false, sc2::ABILITY_ID::BUILD_HATCHERY, 0, { sc2::UNIT_TYPEID::ZERG_DRONE }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_EXTRACTOR] =                  { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false,  true, false, false, false, sc2::ABILITY_ID::BUILD_EXTRACTOR, 0, { sc2::UNIT_TYPEID::ZERG_DRONE }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL] =               { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_SPAWNINGPOOL, 0, { sc2::UNIT_TYPEID::ZERG_DRONE }, { sc2::UNIT_TYPEID::ZERG_HATCHERY, sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER] =           { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_EVOLUTIONCHAMBER, 0, { sc2::UNIT_TYPEID::ZERG_DRONE }, { sc2::UNIT_TYPEID::ZERG_HATCHERY, sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_BANELINGNEST] =               { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_BANELINGNEST, 0, { sc2::UNIT_TYPEID::ZERG_DRONE }, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN] =               { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_HYDRALISKDEN, 0, { sc2::UNIT_TYPEID::ZERG_DRONE }, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT] =             { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_INFESTATIONPIT, 0, { sc2::UNIT_TYPEID::ZERG_DRONE }, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_NYDUSCANAL] =                 { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_NYDUSWORM, 0, { sc2::UNIT_TYPEID::ZERG_DRONE }, { sc2::UNIT_TYPEID::ZERG_NYDUSNETWORK }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_NYDUSNETWORK] =               { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_NYDUSNETWORK, 0, { sc2::UNIT_TYPEID::ZERG_DRONE }, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_ROACHWARREN] =                { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_ROACHWARREN, 0, { sc2::UNIT_TYPEID::ZERG_DRONE }, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_SPINECRAWLER] =               { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_SPINECRAWLER, 0, { sc2::UNIT_TYPEID::ZERG_DRONE }, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_SPIRE] =                      { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_SPIRE, 0, { sc2::UNIT_TYPEID::ZERG_DRONE }, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_GREATERSPIRE] =               { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::MORPH_GREATERSPIRE, 0, { sc2::UNIT_TYPEID::ZERG_SPIRE }, { sc2::UNIT_TYPEID::ZERG_HIVE }, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_SPORECRAWLER] =               { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_SPORECRAWLER, 0, { sc2::UNIT_TYPEID::ZERG_DRONE }, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN] =            { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_ULTRALISKCAVERN, 0, { sc2::UNIT_TYPEID::ZERG_DRONE }, { sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_LAIR] =                       { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false,  true, false, sc2::ABILITY_ID::MORPH_LAIR, 0, { sc2::UNIT_TYPEID::ZERG_HATCHERY }, {}, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_HIVE] =                       { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false,  true, false, sc2::ABILITY_ID::MORPH_HIVE, 0, { sc2::UNIT_TYPEID::ZERG_LAIR }, {}, {} };  

    // Zerg Units                                                                          m  g  s  t  unit  bld    wrk    rfn    sup    hall   add
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_OVERLORD] =                   { sc2::Race::Zerg, 0, 0, 0, 0, true, false, false, false,  true, false, false, sc2::ABILITY_ID::TRAIN_OVERLORD, 0, { sc2::UNIT_TYPEID::ZERG_LARVA }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_BANELING] =                   { sc2::Race::Zerg, 0, 0, 0, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_BANELING, 0, { sc2::UNIT_TYPEID::ZERG_LARVA }, { sc2::UNIT_TYPEID::ZERG_BANELINGNEST }, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_CORRUPTOR] =                  { sc2::Race::Zerg, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_CORRUPTOR, 0, { sc2::UNIT_TYPEID::ZERG_LARVA }, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_DRONE] =                      { sc2::Race::Zerg, 0, 0, 1, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_DRONE, 0, { sc2::UNIT_TYPEID::ZERG_LARVA }, {}, {} }; 
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_HYDRALISK] =                  { sc2::Race::Zerg, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_HYDRALISK, 0, { sc2::UNIT_TYPEID::ZERG_LARVA }, { sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN, sc2::UNIT_TYPEID::ZERG_LURKERDENMP }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_INFESTOR] =                   { sc2::Race::Zerg, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_INFESTOR, 0, { sc2::UNIT_TYPEID::ZERG_LARVA }, { sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_MUTALISK] =                   { sc2::Race::Zerg, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_MUTALISK, 0, { sc2::UNIT_TYPEID::ZERG_LARVA }, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_ROACH] =                      { sc2::Race::Zerg, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_ROACH, 0, { sc2::UNIT_TYPEID::ZERG_LARVA }, { sc2::UNIT_TYPEID::ZERG_ROACHWARREN }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_SWARMHOSTMP] =                { sc2::Race::Zerg, 0, 0, 3, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_SWARMHOST, 0, { sc2::UNIT_TYPEID::ZERG_LARVA }, { sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_ULTRALISK] =                  { sc2::Race::Zerg, 0, 0, 6, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_ULTRALISK, 0, { sc2::UNIT_TYPEID::ZERG_LARVA }, { sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_VIPER] =                      { sc2::Race::Zerg, 0, 0, 3, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_VIPER, 0, { sc2::UNIT_TYPEID::ZERG_LARVA }, { sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_ZERGLING] =                   { sc2::Race::Zerg, 0, 0, 1, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_ZERGLING, 0, { sc2::UNIT_TYPEID::ZERG_LARVA }, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_QUEEN] =                      { sc2::Race::Zerg, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_QUEEN, 0, { sc2::UNIT_TYPEID::ZERG_HATCHERY }, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_LARVA] =                      { sc2::Race::Zerg, 0, 0, 2, 0, true, false, false, false, false, false, false, 0, 0, { 0 }, { 0 }, {} };
    m_unitTypeData[sc2::UNIT_TYPEID::ZERG_EGG] =                        { sc2::Race::Zerg, 0, 0, 2, 0, true, false, false, false, false, false, false, 0, 0, { 0 }, { 0 }, {} };

    // Set the Mineral / Gas cost of each unit
    for (auto & kv : m_unitTypeData)
    {
        if (kv.first == 0) { continue; }
        
        auto & data = m_bot.Observation()->GetUnitTypeData();

        kv.second.mineralCost = m_bot.Observation()->GetUnitTypeData()[kv.first].mineral_cost;
        kv.second.gasCost     = m_bot.Observation()->GetUnitTypeData()[kv.first].vespene_cost;
    }
}

void TechTree::initUpgradeData()
{
    // 0 data for null / error return
    m_upgradeData[0] = TypeData();

    // Terran Upgrades
    m_upgradeData[sc2::UPGRADE_ID::BANSHEECLOAK] =                      { sc2::Race::Terran, 100, 100, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_BANSHEECLOAKINGFIELD, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::BANSHEESPEED] =                      { sc2::Race::Terran, 200, 200, 0, 2720, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_BANSHEEHYPERFLIGHTROTORS, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::BATTLECRUISERENABLESPECIALIZATIONS]= { sc2::Race::Terran, 150, 150, 0,  960, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_BATTLECRUISERWEAPONREFIT, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::DRILLCLAWS] =                        { sc2::Race::Terran, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_DRILLINGCLAWS, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::HIGHCAPACITYBARRELS] =               { sc2::Race::Terran, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_INFERNALPREIGNITER, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::HISECAUTOTRACKING] =                 { sc2::Race::Terran, 100, 100, 0, 1280, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_HISECAUTOTRACKING, 0, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::LIBERATORAGRANGEUPGRADE] =           { sc2::Race::Terran, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ADVANCEDBALLISTICS, 0, { sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::MAGFIELDLAUNCHERS] =                 { sc2::Race::Terran, 100, 100, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_MAGFIELDLAUNCHERS, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::MEDIVACINCREASESPEEDBOOST] =         { sc2::Race::Terran, 100, 100, 0, 1280, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_HIGHCAPACITYFUELTANKS, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::NEOSTEELFRAME] =                     { sc2::Race::Terran, 100, 100, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_NEOSTEELFRAME, 0, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PERSONALCLOAKING] =                  { sc2::Race::Terran, 150, 150, 0, 1920, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PERSONALCLOAKING, 0, { sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PUNISHERGRENADES] =                  { sc2::Race::Terran,  50,  50, 0,  960, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_CONCUSSIVESHELLS, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::RAVENCORVIDREACTOR] =                { sc2::Race::Terran, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_RAVENCORVIDREACTOR, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::RAVENRECALIBRATEDEXPLOSIVES] =       { sc2::Race::Terran, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_RAVENRECALIBRATEDEXPLOSIVES, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::SHIELDWALL] =                        { sc2::Race::Terran, 100, 100, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_COMBATSHIELD, 0, { sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::STIMPACK] =                          { sc2::Race::Terran, 100, 100, 0, 2720, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_STIMPACK, 0, { sc2::UNIT_TYPEID::TERRAN_SCV }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANBUILDINGARMOR] =               { sc2::Race::Terran, 150, 150, 0, 2240, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANSTRUCTUREARMORUPGRADE, 0, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL1] =        { sc2::Race::Terran, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL1, 0, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL2] =        { sc2::Race::Terran, 175, 175, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL2, 0, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL3] =        { sc2::Race::Terran, 250, 250, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL3, 0, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL1] =       { sc2::Race::Terran, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL1, 0, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL2] =       { sc2::Race::Terran, 175, 175, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL2, 0, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL3] =       { sc2::Race::Terran, 250, 250, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL3, 0, { sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY }, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL1] =           { sc2::Race::Terran, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL1, 0, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL2] =           { sc2::Race::Terran, 175, 175, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL2, 0, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {}, {sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL3] =           { sc2::Race::Terran, 250, 250, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL3, 0, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {}, {sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL1] =  { sc2::Race::Terran, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL1, 0, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL2] =  { sc2::Race::Terran, 175, 175, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL2, 0, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {}, {sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL3] =  { sc2::Race::Terran, 250, 250, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL3, 0, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {}, {sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL1] =        { sc2::Race::Terran, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL1, 0, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL2] =        { sc2::Race::Terran, 175, 175, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL2, 0, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {}, {sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL3] =        { sc2::Race::Terran, 250, 250, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL3, 0, { sc2::UNIT_TYPEID::TERRAN_ARMORY }, {}, {sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL2} };

    // Protoss Upgrades
    m_upgradeData[sc2::UPGRADE_ID::ADEPTPIERCINGATTACK] =               { sc2::Race::Protoss, 100, 100, 0, 2240, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ADEPTRESONATINGGLAIVES, 0, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::BLINKTECH] =                         { sc2::Race::Protoss, 150, 150, 0, 2720, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_BLINK, 0, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::CARRIERLAUNCHSPEEDUPGRADE] =         { sc2::Race::Protoss, 150, 150, 0, 1280, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_INTERCEPTORGRAVITONCATAPULT, 0, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::CHARGE] =                            { sc2::Race::Protoss, 100, 100, 0, 2240, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_CHARGE, 0, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::DARKTEMPLARBLINKUPGRADE] =           { sc2::Race::Protoss, 100, 100, 0, 2720, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_SHADOWSTRIKE, 0, { sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::EXTENDEDTHERMALLANCE] =              { sc2::Race::Protoss, 200, 200, 0, 2240, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_EXTENDEDTHERMALLANCE, 0, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::GRAVITICDRIVE] =                     { sc2::Race::Protoss, 100, 100, 0, 1280, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_GRAVITICDRIVE, 0, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::OBSERVERGRAVITICBOOSTER] =           { sc2::Race::Protoss, 100, 100, 0, 1280, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_GRAVITICBOOSTER, 0, { sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PHOENIXRANGEUPGRADE] =               { sc2::Race::Protoss, 150, 150, 0, 1440, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PHOENIXANIONPULSECRYSTALS, 0, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL1] =            { sc2::Race::Protoss, 150, 150, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL1, 0,   { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL2] =            { sc2::Race::Protoss, 225, 225, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL2, 0,   { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, {sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL3] =            { sc2::Race::Protoss, 300, 300, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL3, 0,   { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, {sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL1] =           { sc2::Race::Protoss, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL1, 0, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL2] =           { sc2::Race::Protoss, 175, 175, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL2, 0, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, {sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL3] =           { sc2::Race::Protoss, 250, 250, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL3, 0, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, { sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON }, {sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL3} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL1] =         { sc2::Race::Protoss, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL1, 0, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL2] =         { sc2::Race::Protoss, 150, 150, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL2, 0, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, { sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL3] =         { sc2::Race::Protoss, 200, 200, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL3, 0, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, { sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL2 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL1] =        { sc2::Race::Protoss, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL1, 0, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL2] =        { sc2::Race::Protoss, 150, 150, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL2, 0, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, { sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL3] =        { sc2::Race::Protoss, 200, 200, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL3, 0, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, { sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL2 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL1] =              { sc2::Race::Protoss, 150, 150, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL1, 0, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL2] =              { sc2::Race::Protoss, 225, 225, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL2, 0, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, { sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL3] =              { sc2::Race::Protoss, 300, 300, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL3, 0, { sc2::UNIT_TYPEID::PROTOSS_FORGE }, { sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL }, { sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::PSISTORMTECH] =                      { sc2::Race::Protoss, 200, 200, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PSISTORM, 0, { sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::WARPGATERESEARCH] =                  { sc2::Race::Protoss,  50,  50, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_WARPGATE, 0, { sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE }, {}, {} };

    // Zerg Upgrades
    m_upgradeData[sc2::UPGRADE_ID::BURROW] =                            { sc2::Race::Zerg, 100, 100, 0, 1600, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_BURROW, 0, { sc2::UNIT_TYPEID::ZERG_HATCHERY, sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::CENTRIFICALHOOKS] =                  { sc2::Race::Zerg, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_CENTRIFUGALHOOKS, 0, { sc2::UNIT_TYPEID::ZERG_BANELINGNEST }, {}, {} }; 
    m_upgradeData[sc2::UPGRADE_ID::CHITINOUSPLATING] =                  { sc2::Race::Zerg, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_CHITINOUSPLATING, 0, { sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::EVOLVEGROOVEDSPINES] =               { sc2::Race::Zerg, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_GROOVEDSPINES, 0, { sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::EVOLVEMUSCULARAUGMENTS] =            { sc2::Race::Zerg, 150, 150, 0, 1600, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_MUSCULARAUGMENTS, 0, { sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::GLIALRECONSTITUTION] =               { sc2::Race::Zerg, 100, 100, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_GLIALREGENERATION, 0, { sc2::UNIT_TYPEID::ZERG_ROACHWARREN }, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_upgradeData[sc2::UPGRADE_ID::INFESTORENERGYUPGRADE] =             { sc2::Race::Zerg, 150, 150, 0, 1280, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PATHOGENGLANDS, 0, { sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::NEURALPARASITE] =                    { sc2::Race::Zerg, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_NEURALPARASITE, 0, { sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::OVERLORDSPEED] =                     { sc2::Race::Zerg, 100, 100, 0,  960, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PNEUMATIZEDCARAPACE, 0, { sc2::UNIT_TYPEID::ZERG_HATCHERY, sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {}, {} };                       
    m_upgradeData[sc2::UPGRADE_ID::TUNNELINGCLAWS] =                    { sc2::Race::Zerg, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TUNNELINGCLAWS, 0, { sc2::UNIT_TYPEID::ZERG_ROACHWARREN }, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL1] =             { sc2::Race::Zerg, 150, 150, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGFLYERARMORLEVEL1, 0, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL2] =             { sc2::Race::Zerg, 225, 225, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGFLYERARMORLEVEL2, 0, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, { sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL3] =             { sc2::Race::Zerg, 300, 300, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGFLYERARMORLEVEL3, 0, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, { sc2::UNIT_TYPEID::ZERG_HIVE }, { sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL2 } };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL1] =            { sc2::Race::Zerg, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGFLYERATTACKLEVEL1, 0, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL2] =            { sc2::Race::Zerg, 175, 175, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGFLYERATTACKLEVEL2, 0, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, { sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL3] =            { sc2::Race::Zerg, 250, 250, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGFLYERATTACKLEVEL3, 0, { sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE }, { sc2::UNIT_TYPEID::ZERG_HIVE }, { sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL2 } };
    m_upgradeData[sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL1] =            { sc2::Race::Zerg, 150, 150, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGGROUNDARMORLEVEL1, 0, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL2] =            { sc2::Race::Zerg, 225, 225, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGGROUNDARMORLEVEL2, 0, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL3] =            { sc2::Race::Zerg, 300, 300, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGGROUNDARMORLEVEL3, 0, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, { sc2::UNIT_TYPEID::ZERG_HIVE }, {sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGLINGATTACKSPEED] =               { sc2::Race::Zerg, 200, 200, 0, 2080, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGLINGADRENALGLANDS, 0, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, { sc2::UNIT_TYPEID::ZERG_HIVE }, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGLINGMOVEMENTSPEED] =             { sc2::Race::Zerg, 100, 100, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGLINGMETABOLICBOOST, 0, { sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL1] =            { sc2::Race::Zerg, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL1, 0, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL2] =            { sc2::Race::Zerg, 150, 150, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL2, 0, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL3] =            { sc2::Race::Zerg, 200, 200, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL3, 0, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, { sc2::UNIT_TYPEID::ZERG_HIVE }, {sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL1] =          { sc2::Race::Zerg, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONSLEVEL1, 0, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL2] =          { sc2::Race::Zerg, 150, 150, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONSLEVEL2, 0, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, { sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_HIVE }, {sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL3] =          { sc2::Race::Zerg, 200, 200, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONSLEVEL3, 0, { sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER }, { sc2::UNIT_TYPEID::ZERG_HIVE }, {sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL2} };
}

const TypeData & TechTree::getData(const sc2::UnitTypeID & type) const
{
    if (m_unitTypeData.find(type) == m_unitTypeData.end())
    {
        //std::cout << "WARNING: Unit type not found: " << sc2::UnitTypeToName(type) << "\n";
        return m_unitTypeData.at(0);
    }

    return m_unitTypeData.at(type);
}

const TypeData & TechTree::getData(const sc2::UpgradeID & type)  const
{
    if (m_upgradeData.find(type) == m_upgradeData.end())
    {
        //std::cout << "WARNING: Upgrade not found: " << sc2::UpgradeIDToName(type) << "\n";
        return m_unitTypeData.at(0);
    }

    return m_upgradeData.at(type);
}

const TypeData & TechTree::getData(const BuildType & type) const
{
    if (type.getBuildType() == BuildTypes::Unit)
    {
        return getData(type.getUnitTypeID());
    }
    else if (type.getBuildType() == BuildTypes::Upgrade)
    {
        return getData(type.getUpgradeID());
    }
    
    BOT_ASSERT(false, "Can't getData this type: %s", type.getName().c_str());

    return m_unitTypeData.at(0);
}
