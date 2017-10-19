#pragma once

#include "Common.h"
#include <map>

class CCBot;


class DistanceMap 
{
    int m_width;
    int m_height;
    CCPosition m_startTile;

    std::vector<std::vector<int>> m_dist;
    std::vector<CCPosition> m_sortedTilePositions;
    
public:
    
    DistanceMap();
    void computeDistanceMap(CCBot & m_bot, const CCPosition & startTile);

    int getDistance(int tileX, int tileY) const;
    int getDistance(const CCPosition & pos) const;

    // given a position, get the position we should move to to minimize distance
    const std::vector<CCPosition> & getSortedTiles() const;
    const CCPosition & getStartTile() const;

    void draw(CCBot & bot) const;
};