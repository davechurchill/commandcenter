#pragma once

#include <map>
#include <vector>
#include "sc2api/sc2_api.h"
#include "DistanceMap.h"

class CCBot;

class BaseLocation
{
    CCBot &               m_bot;
    DistanceMap                 m_distanceMap;

    sc2::Point2D                m_depotPosition;
    sc2::Point2D                m_centerOfResources;
    std::vector<sc2::Unit>      m_geysers;
    std::vector<sc2::Unit>      m_minerals;

    std::vector<sc2::Point2D>   m_mineralPositions;
    std::vector<sc2::Point2D>   m_geyserPositions;

    std::map<int, bool>         m_isPlayerOccupying;
    std::map<int, bool>         m_isPlayerStartLocation;
        
    int                         m_baseID;
    float                       m_left;
    float                       m_right;
    float                       m_top;
    float                       m_bottom;
    bool                        m_isStartLocation;
    
public:

    BaseLocation(CCBot & bot, int baseID, const std::vector<sc2::Unit> & resources);
    
    int getGroundDistance(const sc2::Point2D & pos) const;
    bool isStartLocation() const;
    bool isPlayerStartLocation(int player) const;
    bool isMineralOnly() const;
    bool containsPosition(const sc2::Point2D & pos) const;
    const sc2::Point2D & getDepotPosition() const;
    const sc2::Point2D & getPosition() const;
    const std::vector<sc2::Unit> & getGeysers() const;
    const std::vector<sc2::Unit> & getMinerals() const;
    bool isOccupiedByPlayer(int player) const;
    bool isExplored() const;
    bool isInResourceBox(int x, int y) const;

    void setPlayerOccupying(int player, bool occupying);

    const std::vector<sc2::Point2D> & getClosestTiles() const;

    void draw();
};
