#include "TechTree.h"
#include "Util.h"
#include "CCBot.h"
#include "MetaType.h"
#include "Timer.hpp"

TechTree::TechTree(CCBot & bot)
    : m_bot(bot)
{

}

void TechTree::onStart()
{
    initUnitTypeData();
    initUpgradeData();
    outputJSON("TechTree.json");
}


#ifdef SC2API
void TechTree::initUnitTypeData()
{
    m_unitTypeData[UnitType(0, m_bot)] = TypeData();

    // Protoss Buildings                                                                                  unit  bld   wrk    rfn    sup    hall   add
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_PYLONOVERCHARGED, m_bot)] =        { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false,  true, false, false, sc2::ABILITY_ID::EFFECT_PHOTONOVERCHARGE, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_MOTHERSHIPCORE, m_bot), UnitType(sc2::UNIT_TYPEID::PROTOSS_PYLON, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_PYLON, m_bot)] =                   { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false,  true, false, false, sc2::ABILITY_ID::BUILD_PYLON, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_PROBE, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_NEXUS, m_bot)] =                   { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false,  true, false, sc2::ABILITY_ID::BUILD_NEXUS, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_PROBE, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR, m_bot)] =             { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false,  true, false, false, false, sc2::ABILITY_ID::BUILD_ASSIMILATOR, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_PROBE, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE, m_bot)] =         { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_CYBERNETICSCORE, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_PROBE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_GATEWAY, m_bot), UnitType(sc2::UNIT_TYPEID::PROTOSS_WARPGATE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE, m_bot)] =              { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_DARKSHRINE, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_PROBE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON, m_bot)] =             { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_FLEETBEACON, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_PROBE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_STARGATE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_FORGE, m_bot)] =                   { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_FORGE, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_PROBE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_NEXUS, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_GATEWAY, m_bot)] =                 { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_GATEWAY, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_PROBE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_NEXUS, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_STARGATE, m_bot)] =                { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_STARGATE, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_PROBE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE, m_bot) }, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON, m_bot)] =            { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_PHOTONCANNON, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_PROBE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_FORGE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY, m_bot)] =             { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_ROBOTICSBAY, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_PROBE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY, m_bot)] =        { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_ROBOTICSFACILITY, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_PROBE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE, m_bot)] =          { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_TEMPLARARCHIVE, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_PROBE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL, m_bot)] =         { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_TWILIGHTCOUNCIL, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_PROBE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_WARPGATE, m_bot)] =                { sc2::Race::Protoss, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::MORPH_WARPGATE, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_GATEWAY, m_bot) }, {}, { sc2::UPGRADE_ID::WARPGATERESEARCH } }; 

    // Protoss Units                                                                                      unit  bld   wrk    rfn    sup    hall   add
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_PROBE, m_bot)] =                   { sc2::Race::Protoss, 0, 0, 1, 0, true, false,  true, false, false, false, false, sc2::ABILITY_ID::TRAIN_PROBE, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_NEXUS, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_MOTHERSHIPCORE, m_bot)] =          { sc2::Race::Protoss, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_MOTHERSHIPCORE, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_NEXUS, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_ZEALOT, m_bot)] =                  { sc2::Race::Protoss, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_ZEALOT, sc2::ABILITY_ID::TRAINWARP_ZEALOT, { UnitType(sc2::UNIT_TYPEID::PROTOSS_GATEWAY, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_SENTRY, m_bot)] =                  { sc2::Race::Protoss, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_SENTRY, sc2::ABILITY_ID::TRAINWARP_SENTRY, { UnitType(sc2::UNIT_TYPEID::PROTOSS_GATEWAY, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_STALKER, m_bot)] =                 { sc2::Race::Protoss, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_STALKER, sc2::ABILITY_ID::TRAINWARP_STALKER, { UnitType(sc2::UNIT_TYPEID::PROTOSS_GATEWAY, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_HIGHTEMPLAR, m_bot)] =             { sc2::Race::Protoss, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_HIGHTEMPLAR, sc2::ABILITY_ID::TRAINWARP_HIGHTEMPLAR, { UnitType(sc2::UNIT_TYPEID::PROTOSS_GATEWAY, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_DARKTEMPLAR, m_bot)] =             { sc2::Race::Protoss, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_DARKTEMPLAR, sc2::ABILITY_ID::TRAINWARP_DARKTEMPLAR, { UnitType(sc2::UNIT_TYPEID::PROTOSS_GATEWAY, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_ADEPT, m_bot)] =                   { sc2::Race::Protoss, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_ADEPT, sc2::ABILITY_ID::TRAINWARP_ADEPT, { UnitType(sc2::UNIT_TYPEID::PROTOSS_GATEWAY, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_COLOSSUS, m_bot)] =                { sc2::Race::Protoss, 0, 0, 6, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_COLOSSUS,  0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_DISRUPTOR, m_bot)] =               { sc2::Race::Protoss, 0, 0, 3, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_DISRUPTOR, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_WARPPRISM, m_bot)] =               { sc2::Race::Protoss, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_WARPPRISM, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_OBSERVER, m_bot)] =                { sc2::Race::Protoss, 0, 0, 1, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_OBSERVER, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY, m_bot) }, {}, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_IMMORTAL, m_bot)] =                { sc2::Race::Protoss, 0, 0, 4, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_IMMORTAL, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY, m_bot) }, {}, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_CARRIER, m_bot)] =                 { sc2::Race::Protoss, 0, 0, 6, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_CARRIER, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_STARGATE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_ORACLE, m_bot)] =                  { sc2::Race::Protoss, 0, 0, 3, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_ORACLE, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_STARGATE, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_PHOENIX, m_bot)] =                 { sc2::Race::Protoss, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_PHOENIX, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_STARGATE, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_VOIDRAY, m_bot)] =                 { sc2::Race::Protoss, 0, 0, 4, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_VOIDRAY, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_STARGATE, m_bot) }, {}, {} };  
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_TEMPEST, m_bot)] =                 { sc2::Race::Protoss, 0, 0, 4, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_TEMPEST, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_STARGATE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_INTERCEPTOR, m_bot)] =             { sc2::Race::Protoss, 0, 0, 0, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::BUILD_INTERCEPTORS, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_CARRIER, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::PROTOSS_ORACLESTASISTRAP, m_bot)] =        { sc2::Race::Protoss, 0, 0, 0, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::BUILD_STASISTRAP, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_ORACLE, m_bot) }, {}, {} }; 

    // Terran Buildings                                                                      m  g  s  t  unit  bld   wrk    rfn    sup    hall   add
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER, m_bot)] =            { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false,  true, false, sc2::ABILITY_ID::BUILD_COMMANDCENTER, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT, m_bot)] =              { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false,  true, false, false, sc2::ABILITY_ID::BUILD_SUPPLYDEPOT, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, {}, {} };  
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_REFINERY, m_bot)] =                 { sc2::Race::Terran, 0, 0, 0, 0, true, true, false,  true, false, false, false, sc2::ABILITY_ID::BUILD_REFINERY, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_ARMORY, m_bot)] =                   { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_ARMORY, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORY, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORYFLYING, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKS, m_bot)] =                 { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_BARRACKS, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOTLOWERED, m_bot) }, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_SENSORTOWER, m_bot)] =              { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_SENSORTOWER, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORY, m_bot)] =                  { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_FACTORY, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKS, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKSFLYING, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_FUSIONCORE, m_bot)] =               { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_FUSIONCORE, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORT, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORTFLYING, m_bot) }, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORT, m_bot)] =                 { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_STARPORT, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORY, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORYFLYING, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY, m_bot)] =             { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_GHOSTACADEMY, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKS, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKSFLYING, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_BUNKER, m_bot)] =                   { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_BUNKER, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKS, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKSFLYING, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY, m_bot)] =           { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_ENGINEERINGBAY, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING, m_bot) }, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_MISSILETURRET, m_bot)] =            { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_MISSILETURRET, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND, m_bot)] =           { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::MORPH_ORBITALCOMMAND, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKS, m_bot) }, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS, m_bot)] =        { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::MORPH_PLANETARYFORTRESS, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY, m_bot) }, {} };

    // Terran Addons                                                                         m  g  s  t  unit  bld   wrk    rfn    sup    hall   add
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKSREACTOR, m_bot)] =          { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, true, sc2::ABILITY_ID::BUILD_REACTOR_BARRACKS, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKS, m_bot) }, {}, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB, m_bot)] =          { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, true, sc2::ABILITY_ID::BUILD_TECHLAB_BARRACKS, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKS, m_bot) }, {}, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORYREACTOR, m_bot)] =           { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, true, sc2::ABILITY_ID::BUILD_REACTOR_FACTORY, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORY, m_bot) }, {}, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB, m_bot)] =           { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, true, sc2::ABILITY_ID::BUILD_TECHLAB_FACTORY, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORY, m_bot) }, {}, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORTREACTOR, m_bot)] =          { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, true, sc2::ABILITY_ID::BUILD_REACTOR_STARPORT, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORT, m_bot) }, {}, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB, m_bot)] =          { sc2::Race::Terran, 0, 0, 0, 0, true, true, false, false, false, false, true, sc2::ABILITY_ID::BUILD_TECHLAB_STARPORT, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORT, m_bot) }, {}, {} };

    // Terran Equivalent Buildings
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOTLOWERED, m_bot)] =       m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT, m_bot)];
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKSFLYING, m_bot)] =           m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKS, m_bot)];
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING, m_bot)] =      m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER, m_bot)];
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORYFLYING, m_bot)] =            m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORY, m_bot)];
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING, m_bot)] =     m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND, m_bot)];
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORTFLYING, m_bot)] =           m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORT, m_bot)];

    // Terran Units                                                                          m  g  s  t  unit  bld    wrk    rfn    sup    hall   add
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot)] =                      { sc2::Race::Terran, 0, 0, 1, 0, true, false,  true, false, false, false, false, sc2::ABILITY_ID::TRAIN_SCV, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_GHOST, m_bot)] =                    { sc2::Race::Terran, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_GHOST, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKS, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_MARAUDER, m_bot)] =                 { sc2::Race::Terran, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_MARAUDER, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKS, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_TECHLAB, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_MARINE, m_bot)] =                   { sc2::Race::Terran, 0, 0, 1, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_MARINE, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKS, m_bot) }, {}, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_REAPER, m_bot)] =                   { sc2::Race::Terran, 0, 0, 1, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_REAPER, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKS, m_bot) }, {}, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_HELLION, m_bot)] =                  { sc2::Race::Terran, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_HELLION, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORY, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_CYCLONE, m_bot)] =                  { sc2::Race::Terran, 0, 0, 3, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_CYCLONE, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORY, m_bot) }, {}, {} };  
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_SIEGETANK, m_bot)] =                { sc2::Race::Terran, 0, 0, 3, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_SIEGETANK, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORY, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_TECHLAB, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_THOR, m_bot)] =                     { sc2::Race::Terran, 0, 0, 6, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_THOR, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORY, m_bot) }, {}, {} };  
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_WIDOWMINE, m_bot)] =                { sc2::Race::Terran, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_WIDOWMINE, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORY, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_NUKE, m_bot)] =                     { sc2::Race::Terran, 0, 0, 0, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::BUILD_NUKE, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_BANSHEE, m_bot)] =                  { sc2::Race::Terran, 0, 0, 3, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_BANSHEE, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORT, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_TECHLAB, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_BATTLECRUISER, m_bot)] =            { sc2::Race::Terran, 0, 0, 6, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_BATTLECRUISER, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORT, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_LIBERATOR, m_bot)] =                { sc2::Race::Terran, 0, 0, 3, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_LIBERATOR, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORT, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_VIKINGFIGHTER, m_bot)] =            { sc2::Race::Terran, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_VIKINGFIGHTER, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORT, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_RAVEN, m_bot)] =                    { sc2::Race::Terran, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_RAVEN, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORT, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_TECHLAB, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB, m_bot), UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_MEDIVAC, m_bot)] =                  { sc2::Race::Terran, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_MEDIVAC, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORT, m_bot) }, {}, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_MULE, m_bot)] =                     { sc2::Race::Terran, 0, 0, 0, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::EFFECT_CALLDOWNMULE, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND, m_bot) }, {}, {} }; 

    // Zerg Buildings                                                                      m  g  s  t  unit  bld   wrk    rfn    sup    hall   add
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_HATCHERY, m_bot)] =                   { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false,  true, false, sc2::ABILITY_ID::BUILD_HATCHERY, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_DRONE, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_EXTRACTOR, m_bot)] =                  { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false,  true, false, false, false, sc2::ABILITY_ID::BUILD_EXTRACTOR, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_DRONE, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL, m_bot)] =               { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_SPAWNINGPOOL, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_DRONE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_HATCHERY, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER, m_bot)] =           { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_EVOLUTIONCHAMBER, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_DRONE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_HATCHERY, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_BANELINGNEST, m_bot)] =               { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_BANELINGNEST, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_DRONE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN, m_bot)] =               { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_HYDRALISKDEN, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_DRONE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT, m_bot)] =             { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_INFESTATIONPIT, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_DRONE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_NYDUSCANAL, m_bot)] =                 { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_NYDUSWORM, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_DRONE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_NYDUSNETWORK, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_NYDUSNETWORK, m_bot)] =               { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_NYDUSNETWORK, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_DRONE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_ROACHWARREN, m_bot)] =                { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_ROACHWARREN, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_DRONE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_SPINECRAWLER, m_bot)] =               { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_SPINECRAWLER, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_DRONE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_SPIRE, m_bot)] =                      { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_SPIRE, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_DRONE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_GREATERSPIRE, m_bot)] =               { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::MORPH_GREATERSPIRE, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_SPIRE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_SPORECRAWLER, m_bot)] =               { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_SPORECRAWLER, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_DRONE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN, m_bot)] =            { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false, false, false, sc2::ABILITY_ID::BUILD_ULTRALISKCAVERN, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_DRONE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot)] =                       { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false,  true, false, sc2::ABILITY_ID::MORPH_LAIR, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_HATCHERY, m_bot) }, {UnitType(sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL, m_bot)}, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot)] =                       { sc2::Race::Zerg, 0, 0, 0, 0, true, true, false, false, false,  true, false, sc2::ABILITY_ID::MORPH_HIVE, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT, m_bot) }, {} };  

    // Zerg Units                                                                          m  g  s  t  unit  bld    wrk    rfn    sup    hall   add
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_OVERLORD, m_bot)] =                   { sc2::Race::Zerg, 0, 0, 0, 0, true, false, false, false,  true, false, false, sc2::ABILITY_ID::TRAIN_OVERLORD, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_LARVA, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_BANELING, m_bot)] =                   { sc2::Race::Zerg, 0, 0, 0, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_BANELING, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_LARVA, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_BANELINGNEST, m_bot) }, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_CORRUPTOR, m_bot)] =                  { sc2::Race::Zerg, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_CORRUPTOR, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_LARVA, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_SPIRE, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_GREATERSPIRE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_DRONE, m_bot)] =                      { sc2::Race::Zerg, 0, 0, 1, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_DRONE, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_LARVA, m_bot) }, {}, {} }; 
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_HYDRALISK, m_bot)] =                  { sc2::Race::Zerg, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_HYDRALISK, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_LARVA, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_LURKERDENMP, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_INFESTOR, m_bot)] =                   { sc2::Race::Zerg, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_INFESTOR, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_LARVA, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_MUTALISK, m_bot)] =                   { sc2::Race::Zerg, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_MUTALISK, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_LARVA, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_SPIRE, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_GREATERSPIRE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_ROACH, m_bot)] =                      { sc2::Race::Zerg, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_ROACH, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_LARVA, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_ROACHWARREN, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_SWARMHOSTMP, m_bot)] =                { sc2::Race::Zerg, 0, 0, 3, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_SWARMHOST, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_LARVA, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_ULTRALISK, m_bot)] =                  { sc2::Race::Zerg, 0, 0, 6, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_ULTRALISK, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_LARVA, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_VIPER, m_bot)] =                      { sc2::Race::Zerg, 0, 0, 3, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_VIPER, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_LARVA, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_ZERGLING, m_bot)] =                   { sc2::Race::Zerg, 0, 0, 1, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_ZERGLING, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_LARVA, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_QUEEN, m_bot)] =                      { sc2::Race::Zerg, 0, 0, 2, 0, true, false, false, false, false, false, false, sc2::ABILITY_ID::TRAIN_QUEEN, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_HATCHERY, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL, m_bot) }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_LARVA, m_bot)] =                      { sc2::Race::Zerg, 0, 0, 2, 0, true, false, false, false, false, false, false, 0, 0, { UnitType() }, { UnitType() }, {} };
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_EGG, m_bot)] =                        { sc2::Race::Zerg, 0, 0, 2, 0, true, false, false, false, false, false, false, 0, 0, { UnitType() }, { UnitType() }, {} };

    // Set the Mineral / Gas cost of each unit
    for (auto & kv : m_unitTypeData)
    {
        if (!kv.first.isValid()) { continue; }
        
        auto & data = m_bot.Observation()->GetUnitTypeData()[kv.first.getAPIUnitType()];
                
        kv.second.mineralCost = data.mineral_cost;
        kv.second.gasCost     = data.vespene_cost;
    }

    // fix the cumulative prices of morphed buildings
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot)].mineralCost -= getData(UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot)).mineralCost;
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot)].mineralCost -= getData(UnitType(sc2::UNIT_TYPEID::ZERG_HATCHERY, m_bot)).mineralCost;
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS, m_bot)].mineralCost -= getData(UnitType(sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER, m_bot)).mineralCost;
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND, m_bot)].mineralCost -= getData(UnitType(sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER, m_bot)).mineralCost;
    m_unitTypeData[UnitType(sc2::UNIT_TYPEID::ZERG_GREATERSPIRE, m_bot)].mineralCost -= getData(UnitType(sc2::UNIT_TYPEID::ZERG_SPIRE, m_bot)).mineralCost;
}

void TechTree::initUpgradeData()
{
    // 0 data for null / error return
    m_upgradeData[0] = TypeData();

    // Terran Upgrades
    m_upgradeData[sc2::UPGRADE_ID::BANSHEECLOAK] =                      { sc2::Race::Terran, 100, 100, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_BANSHEECLOAKINGFIELD, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::BANSHEESPEED] =                      { sc2::Race::Terran, 200, 200, 0, 2720, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_BANSHEEHYPERFLIGHTROTORS, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::BATTLECRUISERENABLESPECIALIZATIONS]= { sc2::Race::Terran, 150, 150, 0,  960, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_BATTLECRUISERWEAPONREFIT, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::DRILLCLAWS] =                        { sc2::Race::Terran, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_DRILLINGCLAWS, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::HIGHCAPACITYBARRELS] =               { sc2::Race::Terran, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_INFERNALPREIGNITER, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::HISECAUTOTRACKING] =                 { sc2::Race::Terran, 100, 100, 0, 1280, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_HISECAUTOTRACKING, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::LIBERATORAGRANGEUPGRADE] =           { sc2::Race::Terran, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ADVANCEDBALLISTICS, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::MAGFIELDLAUNCHERS] =                 { sc2::Race::Terran, 100, 100, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_MAGFIELDLAUNCHERS, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::MEDIVACINCREASESPEEDBOOST] =         { sc2::Race::Terran, 100, 100, 0, 1280, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_HIGHCAPACITYFUELTANKS, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::NEOSTEELFRAME] =                     { sc2::Race::Terran, 100, 100, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_NEOSTEELFRAME, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PERSONALCLOAKING] =                  { sc2::Race::Terran, 150, 150, 0, 1920, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PERSONALCLOAKING, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PUNISHERGRENADES] =                  { sc2::Race::Terran,  50,  50, 0,  960, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_CONCUSSIVESHELLS, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::RAVENCORVIDREACTOR] =                { sc2::Race::Terran, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_RAVENCORVIDREACTOR, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::RAVENRECALIBRATEDEXPLOSIVES] =       { sc2::Race::Terran, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_RAVENRECALIBRATEDEXPLOSIVES, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::SHIELDWALL] =                        { sc2::Race::Terran, 100, 100, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_COMBATSHIELD, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::STIMPACK] =                          { sc2::Race::Terran, 100, 100, 0, 2720, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_STIMPACK, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_SCV, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANBUILDINGARMOR] =               { sc2::Race::Terran, 150, 150, 0, 2240, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANSTRUCTUREARMORUPGRADE, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL1] =        { sc2::Race::Terran, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL1, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL2] =        { sc2::Race::Terran, 175, 175, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL2, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_ARMORY, m_bot) }, {sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL3] =        { sc2::Race::Terran, 250, 250, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL3, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_ARMORY, m_bot) }, {sc2::UPGRADE_ID::TERRANINFANTRYARMORSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL1] =       { sc2::Race::Terran, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL1, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL2] =       { sc2::Race::Terran, 175, 175, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL2, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_ARMORY, m_bot) }, {sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL3] =       { sc2::Race::Terran, 250, 250, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL3, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY, m_bot) }, { UnitType(sc2::UNIT_TYPEID::TERRAN_ARMORY, m_bot) }, {sc2::UPGRADE_ID::TERRANINFANTRYWEAPONSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL1] =           { sc2::Race::Terran, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL1, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_ARMORY, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL2] =           { sc2::Race::Terran, 175, 175, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL2, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_ARMORY, m_bot) }, {}, {sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL3] =           { sc2::Race::Terran, 250, 250, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL3, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_ARMORY, m_bot) }, {}, {sc2::UPGRADE_ID::TERRANSHIPWEAPONSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL1] =  { sc2::Race::Terran, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL1, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_ARMORY, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL2] =  { sc2::Race::Terran, 175, 175, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL2, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_ARMORY, m_bot) }, {}, {sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL3] =  { sc2::Race::Terran, 250, 250, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL3, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_ARMORY, m_bot) }, {}, {sc2::UPGRADE_ID::TERRANVEHICLEANDSHIPARMORSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL1] =        { sc2::Race::Terran, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL1, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_ARMORY, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL2] =        { sc2::Race::Terran, 175, 175, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL2, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_ARMORY, m_bot) }, {}, {sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL3] =        { sc2::Race::Terran, 250, 250, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL3, 0, { UnitType(sc2::UNIT_TYPEID::TERRAN_ARMORY, m_bot) }, {}, {sc2::UPGRADE_ID::TERRANVEHICLEWEAPONSLEVEL2} };

    // Protoss Upgrades
    m_upgradeData[sc2::UPGRADE_ID::ADEPTPIERCINGATTACK] =               { sc2::Race::Protoss, 100, 100, 0, 2240, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ADEPTRESONATINGGLAIVES, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::BLINKTECH] =                         { sc2::Race::Protoss, 150, 150, 0, 2720, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_BLINK, 0,                   { UnitType(sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::CARRIERLAUNCHSPEEDUPGRADE] =         { sc2::Race::Protoss, 150, 150, 0, 1280, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_INTERCEPTORGRAVITONCATAPULT, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::CHARGE] =                            { sc2::Race::Protoss, 100, 100, 0, 2240, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_CHARGE, 0,                  { UnitType(sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::DARKTEMPLARBLINKUPGRADE] =           { sc2::Race::Protoss, 100, 100, 0, 2720, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_SHADOWSTRIKE, 0,            { UnitType(sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::EXTENDEDTHERMALLANCE] =              { sc2::Race::Protoss, 200, 200, 0, 2240, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_EXTENDEDTHERMALLANCE, 0,    { UnitType(sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::GRAVITICDRIVE] =                     { sc2::Race::Protoss, 100, 100, 0, 1280, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_GRAVITICDRIVE, 0,           { UnitType(sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::OBSERVERGRAVITICBOOSTER] =           { sc2::Race::Protoss, 100, 100, 0, 1280, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_GRAVITICBOOSTER, 0,         { UnitType(sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PHOENIXRANGEUPGRADE] =               { sc2::Race::Protoss, 150, 150, 0, 1440, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PHOENIXANIONPULSECRYSTALS, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL1] =            { sc2::Race::Protoss, 150, 150, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL1, 0,   { UnitType(sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL2] =            { sc2::Race::Protoss, 225, 225, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL2, 0,   { UnitType(sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON, m_bot) }, {sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL3] =            { sc2::Race::Protoss, 300, 300, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL3, 0,   { UnitType(sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON, m_bot) }, {sc2::UPGRADE_ID::PROTOSSAIRARMORSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL1] =           { sc2::Race::Protoss, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL1, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL2] =           { sc2::Race::Protoss, 175, 175, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL2, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON, m_bot) }, {sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL3] =           { sc2::Race::Protoss, 250, 250, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL3, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON, m_bot) }, {sc2::UPGRADE_ID::PROTOSSAIRWEAPONSLEVEL3} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL1] =         { sc2::Race::Protoss, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL1, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_FORGE, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL2] =         { sc2::Race::Protoss, 150, 150, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL2, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_FORGE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL, m_bot) }, { sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL3] =         { sc2::Race::Protoss, 200, 200, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL3, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_FORGE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL, m_bot) }, { sc2::UPGRADE_ID::PROTOSSGROUNDARMORSLEVEL2 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL1] =        { sc2::Race::Protoss, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL1, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_FORGE, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL2] =        { sc2::Race::Protoss, 150, 150, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL2, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_FORGE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL, m_bot) }, { sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL3] =        { sc2::Race::Protoss, 200, 200, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL3, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_FORGE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL, m_bot) }, { sc2::UPGRADE_ID::PROTOSSGROUNDWEAPONSLEVEL2 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL1] =              { sc2::Race::Protoss, 150, 150, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL1, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_FORGE, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL2] =              { sc2::Race::Protoss, 225, 225, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL2, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_FORGE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL, m_bot) }, { sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL3] =              { sc2::Race::Protoss, 300, 300, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL3, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_FORGE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL, m_bot) }, { sc2::UPGRADE_ID::PROTOSSSHIELDSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::PSISTORMTECH] =                      { sc2::Race::Protoss, 200, 200, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PSISTORM, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::WARPGATERESEARCH] =                  { sc2::Race::Protoss,  50,  50, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_WARPGATE, 0, { UnitType(sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE, m_bot) }, {}, {} };

    // Zerg Upgrades
    m_upgradeData[sc2::UPGRADE_ID::BURROW] =                            { sc2::Race::Zerg, 100, 100, 0, 1600, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_BURROW, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_HATCHERY, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::CENTRIFICALHOOKS] =                  { sc2::Race::Zerg, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_CENTRIFUGALHOOKS, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_BANELINGNEST, m_bot) }, {}, {} }; 
    m_upgradeData[sc2::UPGRADE_ID::CHITINOUSPLATING] =                  { sc2::Race::Zerg, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_CHITINOUSPLATING, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::EVOLVEGROOVEDSPINES] =               { sc2::Race::Zerg, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_GROOVEDSPINES, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::EVOLVEMUSCULARAUGMENTS] =            { sc2::Race::Zerg, 150, 150, 0, 1600, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_MUSCULARAUGMENTS, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::GLIALRECONSTITUTION] =               { sc2::Race::Zerg, 100, 100, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_GLIALREGENERATION, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_ROACHWARREN, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {} };
    m_upgradeData[sc2::UPGRADE_ID::INFESTORENERGYUPGRADE] =             { sc2::Race::Zerg, 150, 150, 0, 1280, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PATHOGENGLANDS, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::NEURALPARASITE] =                    { sc2::Race::Zerg, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_NEURALPARASITE, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::OVERLORDSPEED] =                     { sc2::Race::Zerg, 100, 100, 0,  960, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_PNEUMATIZEDCARAPACE, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_HATCHERY, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {}, {} };                       
    m_upgradeData[sc2::UPGRADE_ID::TUNNELINGCLAWS] =                    { sc2::Race::Zerg, 150, 150, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_TUNNELINGCLAWS, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_ROACHWARREN, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL1] =             { sc2::Race::Zerg, 150, 150, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGFLYERARMORLEVEL1, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_SPIRE, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_GREATERSPIRE, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL2] =             { sc2::Race::Zerg, 225, 225, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGFLYERARMORLEVEL2, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_SPIRE, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_GREATERSPIRE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, { sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL3] =             { sc2::Race::Zerg, 300, 300, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGFLYERARMORLEVEL3, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_SPIRE, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_GREATERSPIRE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, { sc2::UPGRADE_ID::ZERGFLYERARMORSLEVEL2 } };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL1] =            { sc2::Race::Zerg, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGFLYERATTACKLEVEL1, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_SPIRE, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_GREATERSPIRE, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL2] =            { sc2::Race::Zerg, 175, 175, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGFLYERATTACKLEVEL2, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_SPIRE, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_GREATERSPIRE, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, { sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL1 } };
    m_upgradeData[sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL3] =            { sc2::Race::Zerg, 250, 250, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGFLYERATTACKLEVEL3, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_SPIRE, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_GREATERSPIRE, m_bot) }, {UnitType( sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, { sc2::UPGRADE_ID::ZERGFLYERWEAPONSLEVEL2 } };
    m_upgradeData[sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL1] =            { sc2::Race::Zerg, 150, 150, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGGROUNDARMORLEVEL1, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL2] =            { sc2::Race::Zerg, 225, 225, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGGROUNDARMORLEVEL2, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL3] =            { sc2::Race::Zerg, 300, 300, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGGROUNDARMORLEVEL3, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {sc2::UPGRADE_ID::ZERGGROUNDARMORSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGLINGATTACKSPEED] =               { sc2::Race::Zerg, 200, 200, 0, 2080, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGLINGADRENALGLANDS, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGLINGMOVEMENTSPEED] =             { sc2::Race::Zerg, 100, 100, 0, 1760, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGLINGMETABOLICBOOST, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL1] =            { sc2::Race::Zerg, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL1, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL2] =            { sc2::Race::Zerg, 150, 150, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL2, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL3] =            { sc2::Race::Zerg, 200, 200, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL3, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {sc2::UPGRADE_ID::ZERGMELEEWEAPONSLEVEL2} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL1] =          { sc2::Race::Zerg, 100, 100, 0, 2560, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONSLEVEL1, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER, m_bot) }, {}, {} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL2] =          { sc2::Race::Zerg, 150, 150, 0, 3040, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONSLEVEL2, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_LAIR, m_bot), UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL1} };
    m_upgradeData[sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL3] =          { sc2::Race::Zerg, 200, 200, 0, 3520, false, false, false, false, false, false, false, sc2::ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONSLEVEL3, 0, { UnitType(sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER, m_bot) }, { UnitType(sc2::UNIT_TYPEID::ZERG_HIVE, m_bot) }, {sc2::UPGRADE_ID::ZERGMISSILEWEAPONSLEVEL2} };
}
#else
void TechTree::initUpgradeData()
{
    
    m_unitTypeData[UnitType(BWAPI::UnitTypes::None, m_bot)] = TypeData();

    for (auto & type : BWAPI::UnitTypes::allUnitTypes())
    {
        TypeData typeData;

        typeData.race = type.getRace();
        typeData.mineralCost = type.mineralPrice();
        typeData.gasCost = type.gasPrice();
        typeData.supplyCost = type.supplyRequired();
        typeData.buildTime = type.buildTime();
        typeData.isUnit = true;
        typeData.isBuilding = type.isBuilding();
        typeData.isWorker = type.isWorker();
        typeData.isRefinery = type.isRefinery();
        typeData.isSupplyProvider = type.supplyProvided() > 0 && !type.isResourceDepot();
        typeData.isResourceDepot = type.isResourceDepot();
        typeData.isAddon = type.isAddon();

        std::vector<UnitType> whatBuilds;
        whatBuilds.push_back(UnitType(type.whatBuilds().first, m_bot));
        typeData.whatBuilds = whatBuilds;

        std::vector<UnitType> requiredUnits;
        for (auto & req : type.requiredUnits())
        {
            requiredUnits.push_back(UnitType(req.first, m_bot));
        }
        typeData.requiredUnits = requiredUnits;

        m_unitTypeData[UnitType(type, m_bot)] = typeData;
    }
}

void TechTree::initUnitTypeData()
{

}
#endif

const TypeData & TechTree::getData(const UnitType & type) const
{
    if (m_unitTypeData.find(type) == m_unitTypeData.end())
    {
        std::cout << "WARNING: Unit type not found: " << type.getName() << "\n";
        return m_unitTypeData.begin()->second;
    }

    return m_unitTypeData.at(type);
}

const TypeData & TechTree::getData(const CCUpgrade & type)  const
{
    if (m_upgradeData.find(type) == m_upgradeData.end())
    {
        //std::cout << "WARNING: Upgrade not found: " << sc2::UpgradeIDToName(type) << "\n";
        return m_unitTypeData.begin()->second;
    }

    return m_upgradeData.at(type);
}

const TypeData & TechTree::getData(const MetaType & type) const
{
    if (type.getMetaType() == MetaTypes::Unit)
    {
        return getData(type.getUnitType());
    }
    else if (type.getMetaType() == MetaTypes::Upgrade)
    {
        return getData(type.getUpgrade());
    }
    
    BOT_ASSERT(false, "Can't getData this type: %s", type.getName().c_str());

    return m_unitTypeData.begin()->second;
}

void TechTree::outputJSON(const std::string & filename) const
{
#ifdef SC2APIXXX
    std::ofstream out(filename);
    out << "{\n";
    std::string q = "\"";
    std::string qcs = "\", ";

    std::vector<std::pair<int, UnitTypeData>> allData;
    for (auto & kv : m_unitTypeData) { allData.push_back({kv.first, kv.second}); }
    for (auto & kv : m_upgradeData) { allData.push_back({kv.first, kv.second}); }

    for (auto & kv : allData)
    {
        std::string name( kv.second.isUnit ? m_bot.Observation()->GetUnitTypeData()[kv.first].name : m_bot.Observation()->GetUpgradeData()[kv.first].name);
        if (name.find("Flying") != std::string::npos) { continue; }
        if (name.find("Lowered") != std::string::npos) { continue; }

        auto & data = kv.second;
               
        out << "    [";
        out << q << name << qcs;
        out << q << Util::GetStringFromRace(data.race) << qcs;
        out << data.mineralCost << ", " << data.gasCost << ", " << data.supplyCost << ", " << data.buildTime << ", ";
        out << data.isUnit << ", " << data.isBuilding << ", " << data.isWorker<< ", " << data.isSupplyDepot << ", " << data.isTownHall << ", " << data.isAddon << ", ";

        out << "[";
        for (size_t i(0); i < data.whatBuilds.size(); ++i) 
        { 
            out << q << m_bot.Observation()->GetUnitTypeData()[data.whatBuilds[i].getAPIUnitType()].name << q;
            if (i < data.whatBuilds.size() - 1) { out << ", "; }
        }
        out << "], ";

        out << "[";
        for (size_t i(0); i < data.requiredUnits.size(); ++i) 
        { 
            out << q << m_bot.Observation()->GetUnitTypeData()[data.requiredUnits[i].getAPIUnitType()].name << q;
            if (i < data.requiredUnits.size() - 1) { out << ", "; }
        }
        out << "], ";

        out << "[";
        for (size_t i(0); i < data.requiredUpgrades.size(); ++i) 
        { 
            out << q << m_bot.Observation()->GetUpgradeData()[data.requiredUpgrades[i]].name << q;
            if (i < data.requiredUpgrades.size() - 1) { out << ", "; }
        }
        out << "] ";

        out << "],\n";
    }

    out << "}";
    out.close();
#else

#endif
}
