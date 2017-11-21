#pragma once

#include "Common.h"
#include "DistanceMap.h"
#include "Unit.h"
#include <map>
#include <vector>

class CCBot;

class BaseLocation
{
    CCBot &                     m_bot;
    DistanceMap                 m_distanceMap;

    CCTilePosition              m_depotPosition;
    CCPosition                  m_centerOfResources;
    std::vector<Unit>           m_geysers;
    std::vector<Unit>           m_minerals;

    std::vector<CCPosition>     m_mineralPositions;
    std::vector<CCPosition>     m_geyserPositions;

    std::map<CCPlayer, bool>    m_isPlayerOccupying;
    std::map<CCPlayer, bool>    m_isPlayerStartLocation;
        
    int                         m_baseID;
    CCPositionType              m_left;
    CCPositionType              m_right;
    CCPositionType              m_top;
    CCPositionType              m_bottom;
    bool                        m_isStartLocation;
    
public:

    BaseLocation(CCBot & bot, int baseID, const std::vector<Unit> & resources);
    
    int getGroundDistance(const CCPosition & pos) const;
    int getGroundDistance(const CCTilePosition & pos) const;
    bool isStartLocation() const;
    bool isPlayerStartLocation(CCPlayer player) const;
    bool isMineralOnly() const;
    bool containsPosition(const CCPosition & pos) const;
    const CCTilePosition & getDepotPosition() const;
    const CCPosition & getPosition() const;
    const std::vector<Unit> & getGeysers() const;
    const std::vector<Unit> & getMinerals() const;
    bool isOccupiedByPlayer(CCPlayer player) const;
    bool isExplored() const;
    bool isInResourceBox(int x, int y) const;

    void setPlayerOccupying(CCPlayer player, bool occupying);

    const std::vector<CCTilePosition> & getClosestTiles() const;

    void draw();
};
