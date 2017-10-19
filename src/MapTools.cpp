#include "MapTools.h"
#include "Util.h"
#include "CCBot.h"

#include <iostream>
#include <sstream>
#include <fstream>

const size_t LegalActions = 4;
const int actionX[LegalActions] ={1, -1, 0, 0};
const int actionY[LegalActions] ={0, 0, 1, -1};

typedef std::vector<std::vector<bool>> vvb;
typedef std::vector<std::vector<int>>  vvi;
typedef std::vector<std::vector<float>>  vvf;

// constructor for MapTools
MapTools::MapTools(CCBot & bot)
    : m_bot     (bot)
    , m_width   (0)
    , m_height  (0)
    , m_maxZ    (0.0f)
    , m_frame   (0)
{

}

void MapTools::onStart()
{
    m_width  = m_bot.Observation()->GetGameInfo().width;
    m_height = m_bot.Observation()->GetGameInfo().height;

    m_walkable       = vvb(m_width, std::vector<bool>(m_height, true));
    m_buildable      = vvb(m_width, std::vector<bool>(m_height, false));
    m_depotBuildable = vvb(m_width, std::vector<bool>(m_height, false));
    m_lastSeen       = vvi(m_width, std::vector<int>(m_height, 0));
    m_sectorNumber   = vvi(m_width, std::vector<int>(m_height, 0));
    m_terrainHeight  = vvf(m_width, std::vector<float>(m_height, 0.0f));

    // Set the boolean grid data from the Map
    for (size_t x(0); x < m_width; ++x)
    {
        for (size_t y(0); y < m_height; ++y)
        {
            m_buildable[x][y]   = canBuild(CCPosition(x+0.5f, y+0.5f));
            m_walkable[x][y]    = m_buildable[x][y] || canWalk(CCPosition(x+0.5f, y+0.5f));
            m_terrainHeight[x][y]   = terainHeight(CCPosition(x+0.5f, y+0.5f));
        }
    }

    for (auto & unit : m_bot.Observation()->GetUnits(sc2::Unit::Alliance::Neutral))
    {
        m_maxZ = std::max(unit->pos.z, m_maxZ);
    }

    computeConnectivity();
}

void MapTools::onFrame()
{
    m_frame++;

    for (int x=0; x<m_width; ++x)
    {
        for (int y=0; y<m_height; ++y)
        {
            if (isVisible(CCPosition((float)x, (float)y)))
            {
                m_lastSeen[x][y] = m_frame;
            }
        }
    }

    draw();
}

void MapTools::computeConnectivity()
{
    // the fringe data structe we will use to do our BFS searches
    std::vector<CCPosition> fringe;
    fringe.reserve(m_width*m_height);
    int sectorNumber = 0;

    // for every tile on the map, do a connected flood fill using BFS
    for (int x=0; x<m_width; ++x)
    {
        for (int y=0; y<m_height; ++y)
        {
            // if the sector is not currently 0, or the map isn't walkable here, then we can skip this tile
            if (getSectorNumber(x, y) != 0 || !isWalkable(x, y))
            {
                continue;
            }

            // increase the sector number, so that walkable tiles have sectors 1-N
            sectorNumber++;

            // reset the fringe for the search and add the start tile to it
            fringe.clear();
            fringe.push_back(CCPosition(x+0.5f, y+0.5f));
            m_sectorNumber[x][y] = sectorNumber;

            // do the BFS, stopping when we reach the last element of the fringe
            for (size_t fringeIndex=0; fringeIndex<fringe.size(); ++fringeIndex)
            {
                auto & tile = fringe[fringeIndex];

                // check every possible child of this tile
                for (size_t a=0; a<LegalActions; ++a)
                {
                    CCPosition nextTile(tile.x + actionX[a], tile.y + actionY[a]);

                    // if the new tile is inside the map bounds, is walkable, and has not been assigned a sector, add it to the current sector and the fringe
                    if (isValid(nextTile) && isWalkable(nextTile) && (getSectorNumber(nextTile) == 0))
                    {
                        m_sectorNumber[(int)nextTile.x][(int)nextTile.y] = sectorNumber;
                        fringe.push_back(nextTile);
                    }
                }
            }
        }
    }
}

bool MapTools::isExplored(const CCPosition & pos) const
{
    if (!isValid(pos)) { return false; }

    sc2::Visibility vis = m_bot.Observation()->GetVisibility(pos);
    return vis == sc2::Visibility::Fogged || vis == sc2::Visibility::Visible;
}

bool MapTools::isVisible(const CCPosition & pos) const
{
    if (!isValid(pos)) { return false; }

    return m_bot.Observation()->GetVisibility(pos) == sc2::Visibility::Visible;
}

bool MapTools::isPowered(const CCPosition & pos) const
{
    for (auto & powerSource : m_bot.Observation()->GetPowerSources())
    {
        if (Util::Dist(pos, powerSource.position) < powerSource.radius)
        {
            return true;
        }
    }

    return false;
}

float MapTools::terrainHeight(float x, float y) const
{
    return m_terrainHeight[(int)x][(int)y];
}

//int MapTools::getGroundDistance(const CCPosition & src, const CCPosition & dest) const
//{
//    return (int)Util::Dist(src, dest);
//}

int MapTools::getGroundDistance(const CCPosition & src, const CCPosition & dest) const
{
    if (_allMaps.size() > 50)
    {
        _allMaps.clear();
    }

    return getDistanceMap(dest).getDistance(src);
}

const DistanceMap & MapTools::getDistanceMap(const CCPosition & tile) const
{
    std::pair<int, int> intTile((int)tile.x, (int)tile.y);

    if (_allMaps.find(intTile) == _allMaps.end())
    {
        _allMaps[intTile] = DistanceMap();
        _allMaps[intTile].computeDistanceMap(m_bot, tile);
    }

    return _allMaps[intTile];
}

int MapTools::getSectorNumber(int x, int y) const
{
    if (!isValid(x, y))
    {
        return 0;
    }

    return m_sectorNumber[x][y];
}

int MapTools::getSectorNumber(const CCPosition & pos) const
{
    return getSectorNumber((int)pos.x, (int)pos.y);
}

bool MapTools::isValid(int x, int y) const
{
    return x >= 0 && y >= 0 && x < m_width && y < m_height;
}

bool MapTools::isValid(const CCPosition & pos) const
{
    return isValid((int)pos.x, (int)pos.y);
}

void MapTools::draw() const
{
#ifdef SC2API
    CCPosition camera = m_bot.Observation()->GetCameraPos();
    for (float x = camera.x - 16.0f; x < camera.x + 16.0f; ++x)
    {
        for (float y = camera.y - 16.0f; y < camera.y + 16.0f; ++y)
        {
            if (!isValid((int)x, (int)y))
            {
                continue;
            }

            if (m_bot.Config().DrawWalkableSectors)
            {
                std::stringstream ss;
                ss << getSectorNumber((int)x, (int)y);
                m_bot.Debug()->DebugTextOut(ss.str(), sc2::Point3D(x + 0.5f, y + 0.5f, m_maxZ + 0.1f), sc2::Colors::Yellow);
            }

            if (m_bot.Config().DrawTileInfo)
            {
                CCColor color = isWalkable((int)x, (int)y) ? sc2::Colors::Green : sc2::Colors::Red;
                if (isWalkable((int)x, (int)y) && !isBuildable((int)x, (int)y))
                {
                    color = sc2::Colors::Yellow;
                }

                drawSquare(x, y, x+1, y+1, color);
            }
        }
    }
#else

#endif
}

void MapTools::drawLine(float x1, float y1, float x2, float y2, const CCColor & color) const
{
#ifdef SC2API
    m_bot.Debug()->DebugLineOut(sc2::Point3D(x1, y1, m_maxZ + 0.2f), sc2::Point3D(x2, y2, m_maxZ + 0.2f), color);
#else
    // BWAPI
#endif
}

void MapTools::drawLine(const CCPosition & min, const CCPosition max, const CCColor & color) const
{
#ifdef SC2API
    m_bot.Debug()->DebugLineOut(sc2::Point3D(min.x, min.y, m_maxZ + 0.2f), sc2::Point3D(max.x, max.y, m_maxZ + 0.2f), color);
#else
    // BWAPI
#endif
}

void MapTools::drawSquare(float x1, float y1, float x2, float y2, const CCColor & color) const
{
#ifdef SC2API
    m_bot.Debug()->DebugLineOut(sc2::Point3D(x1, y1, m_maxZ), sc2::Point3D(x1+1, y1, m_maxZ), color);
    m_bot.Debug()->DebugLineOut(sc2::Point3D(x1, y1, m_maxZ), sc2::Point3D(x1, y1+1, m_maxZ), color);
    m_bot.Debug()->DebugLineOut(sc2::Point3D(x1+1, y1+1, m_maxZ), sc2::Point3D(x1+1, y1, m_maxZ), color);
    m_bot.Debug()->DebugLineOut(sc2::Point3D(x1+1, y1+1, m_maxZ), sc2::Point3D(x1, y1+1, m_maxZ), color);
#else

#endif
}

void MapTools::drawBox(float x1, float y1, float x2, float y2, const CCColor & color) const
{
#ifdef SC2API
    m_bot.Debug()->DebugBoxOut(sc2::Point3D(x1, y1, m_maxZ + 2.0f), sc2::Point3D(x2, y2, m_maxZ-5.0f), color);
#else

#endif
}

void MapTools::drawBox(const CCPosition & min, const CCPosition max, const CCColor & color) const
{
#ifdef SC2API
    m_bot.Debug()->DebugBoxOut(sc2::Point3D(min.x, min.y, m_maxZ + 2.0f), sc2::Point3D(max.x, max.y, m_maxZ-5.0f), color);
#else

#endif
}

void MapTools::drawCircle(const CCPosition & pos, float radius, const CCColor & color) const
{
#ifdef SC2API
    m_bot.Debug()->DebugSphereOut(sc2::Point3D(pos.x, pos.y, m_maxZ), radius, color);
#else

#endif
}

void MapTools::drawCircle(float x, float y, float radius, const CCColor & color) const
{
#ifdef SC2API
    m_bot.Debug()->DebugSphereOut(sc2::Point3D(x, y, m_maxZ), radius, color);
#else

#endif
}


void MapTools::drawText(const CCPosition & pos, const std::string & str, const CCColor & color) const
{
#ifdef SC2API
    m_bot.Debug()->DebugTextOut(str, sc2::Point3D(pos.x, pos.y, m_maxZ), color);
#else

#endif
}

void MapTools::drawTextScreen(const CCPosition & pos, const std::string & str, const CCColor & color) const
{
#ifdef SC2API
    m_bot.Debug()->DebugTextOut(str, pos, color);
#else

#endif
}

bool MapTools::isConnected(int x1, int y1, int x2, int y2) const
{
    if (!isValid(x1, y1) || !isValid(x2, y2))
    {
        return false;
    }

    int s1 = getSectorNumber(x1, y1);
    int s2 = getSectorNumber(x2, y2);

    return s1 != 0 && (s1 == s2);
}

bool MapTools::isConnected(const CCPosition & p1, const CCPosition & p2) const
{
    return isConnected((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y);
}

bool MapTools::isBuildable(int x, int y) const
{
    if (!isValid(x, y))
    {
        return false;
    }

    return m_buildable[x][y];
}

bool MapTools::canBuildTypeAtPosition(int x, int y, CCUnitType type) const
{
    return m_bot.Query()->Placement(m_bot.Data(type).buildAbility, CCPosition((float)x, (float)y));
}

bool MapTools::isBuildable(const CCPosition & tile) const
{
    return isBuildable((int)tile.x, (int)tile.y);
}

void MapTools::printMap()
{
    std::stringstream ss;
    for (int y(0); y < m_height; ++y)
    {
        for (int x(0); x < m_width; ++x)
        {
            ss << isWalkable(x, y);
        }

        ss << "\n";
    }

    std::ofstream out("map.txt");
    out << ss.str();
    out.close();
}

bool MapTools::isDepotBuildableTile(const CCPosition & tile) const
{
    if (!isValid(tile))
    {
        return false;
    }

    return m_depotBuildable[(int)tile.x][(int)tile.y];
}

bool MapTools::isWalkable(int x, int y) const
{
    if (!isValid(x, y))
    {
        return false;
    }

    return m_walkable[x][y];
}

bool MapTools::isWalkable(const CCPosition & tile) const
{
    return isWalkable((int)tile.x, (int)tile.y);
}

int MapTools::width() const
{
    return m_width;
}

int MapTools::height() const
{
    return m_height;
}

const std::vector<CCPosition> & MapTools::getClosestTilesTo(const CCPosition & pos) const
{
    return getDistanceMap(pos).getSortedTiles();
}


void MapTools::drawBoxAroundUnit(CCUnit unit, CCColor color) const
{
    if (!unit) { return; }

    sc2::Point3D p_min = unit->pos;
    p_min.x -= 2.0f;
    p_min.y -= 2.0f;
    p_min.z -= 2.0f;

    sc2::Point3D p_max = unit->pos;
    p_max.x += 2.0f;
    p_max.y += 2.0f;
    p_max.z += 2.0f;

    drawSquare(unit->pos.x - 2.0f, unit->pos.y - 2.0f, unit->pos.x + 2.0f, unit->pos.y + 2.0f, color);
}

CCPosition MapTools::getLeastRecentlySeenPosition() const
{
    int minSeen = std::numeric_limits<int>::max();
    CCPosition leastSeen(0.0f, 0.0f);
    const BaseLocation * baseLocation = m_bot.Bases().getPlayerStartingBaseLocation(Players::Self);

    for (auto & tile : baseLocation->getClosestTiles())
    {
        BOT_ASSERT(isValid(tile), "How is this tile not valid?");

        int lastSeen = m_lastSeen[(int)tile.x][(int)tile.y];
        if (lastSeen < minSeen)
        {
            minSeen = lastSeen;
            leastSeen = tile;
        }
    }

    return leastSeen;
}

bool MapTools::canWalk(const CCPosition & point) 
{
#ifdef SC2API
    auto & info = m_bot.Observation()->GetGameInfo();
    sc2::Point2DI pointI((int)point.x, (int)point.y);
    if (pointI.x < 0 || pointI.x >= info.width || pointI.y < 0 || pointI.y >= info.width)
    {
        return false;
    }

    assert(info.pathing_grid.data.size() == info.width * info.height);
    unsigned char encodedPlacement = info.pathing_grid.data[pointI.x + ((info.height - 1) - pointI.y) * info.width];
    bool decodedPlacement = encodedPlacement == 255 ? false : true;
    return decodedPlacement;
#else
    // BWAPI
#endif
}

bool MapTools::canBuild(const CCPosition & point) 
{
#ifdef SC2API
    auto & info = m_bot.Observation()->GetGameInfo();
    sc2::Point2DI pointI((int)point.x, (int)point.y);
    if (pointI.x < 0 || pointI.x >= info.width || pointI.y < 0 || pointI.y >= info.width)
    {
        return false;
    }

    assert(info.placement_grid.data.size() == info.width * info.height);
    unsigned char encodedPlacement = info.placement_grid.data[pointI.x + ((info.height - 1) - pointI.y) * info.width];
    bool decodedPlacement = encodedPlacement == 255 ? true : false;
    return decodedPlacement;
#else

#endif
}

float MapTools::terainHeight(const CCPosition & point) 
{
#ifdef SC2API
    auto & info = m_bot.Observation()->GetGameInfo();
    sc2::Point2DI pointI((int)point.x, (int)point.y);
    if (pointI.x < 0 || pointI.x >= info.width || pointI.y < 0 || pointI.y >= info.width)
    {
        return 0.0f;
    }

    assert(info.terrain_height.data.size() == info.width * info.height);
    unsigned char encodedHeight = info.terrain_height.data[pointI.x + ((info.height - 1) - pointI.y) * info.width];
    float decodedHeight = -100.0f + 200.0f * float(encodedHeight) / 255.0f;
    return decodedHeight;
#else
    return 0;
#endif
}