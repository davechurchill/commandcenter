#pragma once

#include <vector>
#include "DistanceMap.h"
#include "UnitType.h"

class CCBot;

class MapTools
{
    CCBot & m_bot;
    int     m_width;
    int     m_height;
    float   m_maxZ;
    int     m_frame;
    

    // a cache of already computed distance maps, which is mutable since it only acts as a cache
    mutable std::map<std::pair<int,int>, DistanceMap>   m_allMaps;   

    std::vector<std::vector<bool>>  m_walkable;         // whether a tile is buildable (includes static resources)
    std::vector<std::vector<bool>>  m_buildable;        // whether a tile is buildable (includes static resources)
    std::vector<std::vector<bool>>  m_depotBuildable;   // whether a depot is buildable on a tile (illegal within 3 tiles of static resource)
    std::vector<std::vector<int>>   m_lastSeen;         // the last time any of our units has seen this position on the map
    std::vector<std::vector<int>>   m_sectorNumber;     // connectivity sector number, two tiles are ground connected if they have the same number
    std::vector<std::vector<float>> m_terrainHeight;        // height of the map at x+0.5, y+0.5
    
    void computeConnectivity();

    int getSectorNumber(int x, int y) const;
        
    void printMap();

    float   terrainHeight(const CCPosition & point) const;
    bool    canBuild(int tileX, int tileY);
    bool    canWalk(int tileX, int tileY);

public:

    MapTools(CCBot & bot);

    void    onStart();
    void    onFrame();
    void    draw() const;

    int     width() const;
    int     height() const;
    float   terrainHeight(float x, float y) const;

    void    drawLine(CCPositionType x1, CCPositionType y1, CCPositionType x2, CCPositionType y2, const CCColor & color = CCColor(255, 255, 255)) const;
    void    drawLine(const CCPosition & p1, const CCPosition & p2, const CCColor & color = CCColor(255, 255, 255)) const;
    void    drawTile(int tileX, int tileY, const CCColor & color = CCColor(255, 255, 255)) const;
    void    drawBox(CCPositionType x1, CCPositionType y1, CCPositionType x2, CCPositionType y2, const CCColor & color = CCColor(255, 255, 255)) const;
    void    drawBox(const CCPosition & tl, const CCPosition & br, const CCColor & color = CCColor(255, 255, 255)) const;
    void    drawCircle(CCPositionType x1, CCPositionType x2, CCPositionType radius, const CCColor & color = CCColor(255, 255, 255)) const;
    void    drawCircle(const CCPosition & pos, CCPositionType radius, const CCColor & color = CCColor(255, 255, 255)) const;
    void    drawText(const CCPosition & pos, const std::string & str, const CCColor & color = CCColor(255, 255, 255)) const;
    void    drawTextScreen(float xPerc, float yPerc, const std::string & str, const CCColor & color = CCColor(255, 255, 255)) const;
    
    bool    isValidTile(int tileX, int tileY) const;
    bool    isValidTile(const CCTilePosition & tile) const;
    bool    isValidPosition(const CCPosition & pos) const;
    bool    isPowered(int tileX, int tileY) const;
    bool    isExplored(int tileX, int tileY) const;
    bool    isExplored(const CCPosition & pos) const;
    bool    isExplored(const CCTilePosition & pos) const;
    bool    isVisible(int tileX, int tileY) const;
    bool    canBuildTypeAtPosition(int tileX, int tileY, const UnitType & type) const;

    const   DistanceMap & getDistanceMap(const CCTilePosition & tile) const;
    const   DistanceMap & getDistanceMap(const CCPosition & tile) const;
    int     getGroundDistance(const CCPosition & src, const CCPosition & dest) const;
    bool    isConnected(int x1, int y1, int x2, int y2) const;
    bool    isConnected(const CCTilePosition & from, const CCTilePosition & to) const;
    bool    isConnected(const CCPosition & from, const CCPosition & to) const;
    bool    isWalkable(int tileX, int tileY) const;
    bool    isWalkable(const CCTilePosition & tile) const;
    
    bool    isBuildable(int tileX, int tileY) const;
    bool    isBuildable(const CCTilePosition & tile) const;
    bool    isDepotBuildableTile(int tileX, int tileY) const;
    
    CCTilePosition getLeastRecentlySeenTile() const;

    // returns a list of all tiles on the map, sorted by 4-direcitonal walk distance from the given position
    const std::vector<CCTilePosition> & getClosestTilesTo(const CCTilePosition & pos) const;
};

