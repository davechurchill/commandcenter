#pragma once

#include <vector>

#include "sc2api/sc2_api.h"
#include "DistanceMap.h"

class CCBot;

class MapTools
{
    CCBot & m_bot;
    int     m_width;
    int     m_height;
    float   m_maxZ;
    int     m_frame;
    

    // a cache of already computed distance maps, which is mutable since it only acts as a cache
    mutable std::map<std::pair<int, int>, DistanceMap>   _allMaps;   

    std::vector<std::vector<bool>>  m_walkable;         // whether a tile is buildable (includes static resources)
    std::vector<std::vector<bool>>  m_buildable;        // whether a tile is buildable (includes static resources)
    std::vector<std::vector<bool>>  m_depotBuildable;   // whether a depot is buildable on a tile (illegal within 3 tiles of static resource)
    std::vector<std::vector<int>>   m_lastSeen;         // the last time any of our units has seen this position on the map
    std::vector<std::vector<int>>   m_sectorNumber;     // connectivity sector number, two tiles are ground connected if they have the same number
    std::vector<std::vector<float>> m_terrainHeight;        // height of the map at x+0.5, y+0.5
    
    void computeConnectivity();

    int getSectorNumber(int x, int y) const;
    int getSectorNumber(const sc2::Point2D & pos) const;
        
    void printMap();

public:

    MapTools(CCBot & bot);

    void    onStart();
    void    onFrame();
    void    draw() const;

    int     width() const;
    int     height() const;
    float   terrainHeight(float x, float y) const;

    void    drawLine(float x1, float y1, float x2, float y2, const sc2::Color & color = sc2::Colors::White) const;
    void    drawLine(const sc2::Point2D & min, const sc2::Point2D max, const sc2::Color & color = sc2::Colors::White) const;
    void    drawSquare(float x1, float y1, float x2, float y2, const sc2::Color & color = sc2::Colors::White) const;
    void    drawBox(float x1, float y1, float x2, float y2, const sc2::Color & color = sc2::Colors::White) const;
    void    drawBox(const sc2::Point2D & min, const sc2::Point2D max, const sc2::Color & color = sc2::Colors::White) const;
    void    drawSphere(float x1, float x2, float radius, const sc2::Color & color = sc2::Colors::White) const;
    void    drawSphere(const sc2::Point2D & pos, float radius, const sc2::Color & color = sc2::Colors::White) const;
    void    drawText(const sc2::Point2D & pos, const std::string & str, const sc2::Color & color = sc2::Colors::White) const;
    void    drawTextScreen(const sc2::Point2D & pos, const std::string & str, const sc2::Color & color = sc2::Colors::White) const;
    void    drawBoxAroundUnit(const UnitTag & uinit, sc2::Color color) const;
    void    drawSphereAroundUnit(const UnitTag & uinit, sc2::Color color) const;
    
    bool    isValid(int x, int y) const;
    bool    isValid(const sc2::Point2D & pos) const;
    bool    isPowered(const sc2::Point2D & pos) const;
    bool    isExplored(const sc2::Point2D & pos) const;
    bool    isVisible(const sc2::Point2D & pos) const;
    bool    canBuildTypeAtPosition(int x, int y, sc2::UnitTypeID type) const;

    const   DistanceMap & getDistanceMap(const sc2::Point2D & tile) const;
    int     getGroundDistance(const sc2::Point2D & src, const sc2::Point2D & dest) const;
    bool    isConnected(int x1, int y1, int x2, int y2) const;
    bool    isConnected(const sc2::Point2D & from, const sc2::Point2D & to) const;
    bool    isWalkable(const sc2::Point2D & pos) const;
    bool    isWalkable(int x, int y) const;
    void    drawLastSeen() const;
    
    bool    isBuildable(const sc2::Point2D & pos) const;
    bool    isBuildable(int x, int y) const;
    bool    isDepotBuildableTile(const sc2::Point2D & pos) const;
    
    sc2::Point2D getLeastRecentlySeenPosition() const;

    // returns a list of all tiles on the map, sorted by 4-direcitonal walk distance from the given position
    const std::vector<sc2::Point2D> & getClosestTilesTo(const sc2::Point2D & pos) const;
};

