#include "DistanceMap.h"
#include "CCBot.h"
#include "Util.h"

const size_t LegalActions = 4;
const int actionX[LegalActions] = {1, -1, 0, 0};
const int actionY[LegalActions] = {0, 0, 1, -1};

DistanceMap::DistanceMap() 
{
    
}

int DistanceMap::getDistance(int tileX, int tileY) const
{ 
    BOT_ASSERT(tileX < m_width && tileY < m_height, "Index out of range: X = %d, Y = %d", tileX, tileY);
    return m_dist[tileX][tileY]; 
}

int DistanceMap::getDistance(const CCTilePosition & pos) const
{ 
    return getDistance(pos.x, pos.y); 
}

int DistanceMap::getDistance(const CCPosition & pos) const
{ 
#ifdef SC2API
    return getDistance(CCTilePosition((int)pos.x, (int)pos.y));
#else
    return getDistance(CCTilePosition(pos));
#endif
}

const std::vector<CCTilePosition> & DistanceMap::getSortedTiles() const
{
    return m_sortedTiles;
}

// Computes m_dist[x][y] = ground distance from (startX, startY) to (x,y)
// Uses BFS, since the map is quite large and DFS may cause a stack overflow
void DistanceMap::computeDistanceMap(CCBot & m_bot, const CCTilePosition & startTile)
{
    m_startTile = startTile;
    m_width = m_bot.Map().width();
    m_height = m_bot.Map().height();
    m_dist = std::vector<std::vector<int>>(m_width, std::vector<int>(m_height, -1));
    m_sortedTiles.reserve(m_width * m_height);

    // the fringe for the BFS we will perform to calculate distances
    std::vector<CCTilePosition> fringe;
    fringe.reserve(m_width * m_height);
    fringe.push_back(startTile);
    m_sortedTiles.push_back(startTile);

    m_dist[(int)startTile.x][(int)startTile.y] = 0;

    for (size_t fringeIndex=0; fringeIndex<fringe.size(); ++fringeIndex)
    {
        auto & tile = fringe[fringeIndex];

        // check every possible child of this tile
        for (size_t a=0; a<LegalActions; ++a)
        {
            CCTilePosition nextTile(tile.x + actionX[a], tile.y + actionY[a]);

            // if the new tile is inside the map bounds, is walkable, and has not been visited yet, set the distance of its parent + 1
            if (m_bot.Map().isWalkable(nextTile) && getDistance(nextTile) == -1)
            {
                m_dist[(int)nextTile.x][(int)nextTile.y] = m_dist[(int)tile.x][(int)tile.y] + 1;
                fringe.push_back(nextTile);
                m_sortedTiles.push_back(nextTile);
            }
        }
    }
}

void DistanceMap::draw(CCBot & bot) const
{
    const int tilesToDraw = 200;
    for (size_t i(0); i < tilesToDraw; ++i)
    {
        auto & tile = m_sortedTiles[i];
        int dist = getDistance(tile);

        CCPosition textPos(tile.x + Util::TileToPosition(0.5), tile.y + Util::TileToPosition(0.5));
        std::stringstream ss;
        ss << dist;

        bot.Map().drawText(textPos, ss.str());
    }
}

const CCTilePosition & DistanceMap::getStartTile() const
{
    return m_startTile;
}