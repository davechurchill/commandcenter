#include "Common.h"
#include "BuildingPlacer.h"
#include "CCBot.h"
#include "Building.h"
#include "Util.h"

BuildingPlacer::BuildingPlacer(CCBot & bot)
    : m_bot(bot)
{

}

void BuildingPlacer::onStart()
{
    m_reserveMap = std::vector< std::vector<bool> >(m_bot.Map().width(), std::vector<bool>(m_bot.Map().height(), false));
}

bool BuildingPlacer::isInResourceBox(int tileX, int tileY) const
{
    return m_bot.Bases().getPlayerStartingBaseLocation(Players::Self)->isInResourceBox(tileX, tileY);
}

// makes final checks to see if a building can be built at a certain location
bool BuildingPlacer::canBuildHere(int bx, int by, const Building & b) const
{
    if (isInResourceBox(bx, by))
    {
        return false;
    }

    // check the reserve map
    for (int x = bx; x < bx + b.type.tileWidth(); x++)
    {
        for (int y = by; y < by + b.type.tileHeight(); y++)
        {
            if (!m_bot.Map().isValidTile(x, y) || m_reserveMap[x][y])
            {
                return false;
            }
        }
    }

    // if it overlaps a base location return false
    if (tileOverlapsBaseLocation(bx, by, b.type))
    {
        return false;
    }

    return true;
}

//returns true if we can build this type of unit here with the specified amount of space.
bool BuildingPlacer::canBuildHereWithSpace(int bx, int by, const Building & b, int buildDist) const
{
    UnitType type = b.type;

    //if we can't build here, we of course can't build here with space
    if (!canBuildHere(bx, by, b))
    {
        return false;
    }

    // height and width of the building
    int width  = b.type.tileWidth();
    int height = b.type.tileHeight();

    // TODO: make sure we leave space for add-ons. These types of units can have addons:

    // define the rectangle of the building spot
    int startx = bx - buildDist;
    int starty = by - buildDist;
    int endx   = bx + width + buildDist;
    int endy   = by + height + buildDist;

    // TODO: recalculate start and end positions for addons

    // if this rectangle doesn't fit on the map we can't build here
    if (startx < 0 || starty < 0 || endx > m_bot.Map().width() || endx < bx + width || endy > m_bot.Map().height())
    {
        return false;
    }

    // if we can't build here, or space is reserved, or it's in the resource box, we can't build here
    for (int x = startx; x < endx; x++)
    {
        for (int y = starty; y < endy; y++)
        {
            if (!b.type.isRefinery())
            {
                if (!buildable(b, x, y) || m_reserveMap[x][y])
                {
                    return false;
                }
            }
        }
    }

    return true;
}

CCTilePosition BuildingPlacer::getBuildLocationNear(const Building & b, int buildDist) const
{
    Timer t;
    t.start();

    // get the precomputed vector of tile positions which are sorted closes to this location
    auto & closestToBuilding = m_bot.Map().getClosestTilesTo(b.desiredPosition);

    double ms1 = t.getElapsedTimeInMilliSec();

    // iterate through the list until we've found a suitable location
    for (size_t i(0); i < closestToBuilding.size() && i < 1000; ++i)
    {
        auto & pos = closestToBuilding[i];

        if (canBuildHereWithSpace(pos.x, pos.y, b, buildDist))
        {
            double ms = t.getElapsedTimeInMilliSec();
            //printf("Building Placer Took %d iterations, lasting %lf ms @ %lf iterations/ms, %lf setup ms\n", (int)i, ms, (i / ms), ms1);

            return pos;
        }
    }

    double ms = t.getElapsedTimeInMilliSec();
    //printf("Building Placer Failure: %s - Took %lf ms\n", b.type.getName().c_str(), ms);

    return CCTilePosition(0, 0);
}

bool BuildingPlacer::tileOverlapsBaseLocation(int x, int y, UnitType type) const
{
    // if it's a resource depot we don't care if it overlaps
    if (type.isResourceDepot())
    {
        return false;
    }

    // dimensions of the proposed location
    int tx1 = x;
    int ty1 = y;
    int tx2 = tx1 + type.tileWidth();
    int ty2 = ty1 + type.tileHeight();

    // for each base location
    for (const BaseLocation * base : m_bot.Bases().getBaseLocations())
    {
        // dimensions of the base location
        int bx1 = (int)base->getDepotPosition().x;
        int by1 = (int)base->getDepotPosition().y;
        int bx2 = bx1 + Util::GetTownHall(m_bot.GetPlayerRace(Players::Self), m_bot).tileWidth();
        int by2 = by1 + Util::GetTownHall(m_bot.GetPlayerRace(Players::Self), m_bot).tileHeight();

        // conditions for non-overlap are easy
        bool noOverlap = (tx2 < bx1) || (tx1 > bx2) || (ty2 < by1) || (ty1 > by2);

        // if the reverse is true, return true
        if (!noOverlap)
        {
            return true;
        }
    }

    // otherwise there is no overlap
    return false;
}

bool BuildingPlacer::buildable(const Building & b, int x, int y) const
{
    // TODO: does this take units on the map into account?
    if (!m_bot.Map().isValidTile(x, y) || !m_bot.Map().canBuildTypeAtPosition(x, y, b.type))
    {
        return false;
    }

    // todo: check that it won't block an addon

    return true;
}

void BuildingPlacer::reserveTiles(int bx, int by, int width, int height)
{
    int rwidth = (int)m_reserveMap.size();
    int rheight = (int)m_reserveMap[0].size();
    for (int x = bx; x < bx + width && x < rwidth; x++)
    {
        for (int y = by; y < by + height && y < rheight; y++)
        {
            m_reserveMap[x][y] = true;
        }
    }
}

void BuildingPlacer::drawReservedTiles()
{
    if (!m_bot.Config().DrawReservedBuildingTiles)
    {
        return;
    }

    int rwidth = (int)m_reserveMap.size();
    int rheight = (int)m_reserveMap[0].size();

    for (int x = 0; x < rwidth; ++x)
    {
        for (int y = 0; y < rheight; ++y)
        {
            if (m_reserveMap[x][y] || isInResourceBox(x, y))
            {
                m_bot.Map().drawTile(x, y, CCColor(255, 255, 0));
            }
        }
    }
}

void BuildingPlacer::freeTiles(int bx, int by, int width, int height)
{
    int rwidth = (int)m_reserveMap.size();
    int rheight = (int)m_reserveMap[0].size();

    for (int x = bx; x < bx + width && x < rwidth; x++)
    {
        for (int y = by; y < by + height && y < rheight; y++)
        {
            m_reserveMap[x][y] = false;
        }
    }
}

CCTilePosition BuildingPlacer::getRefineryPosition()
{
    CCPosition closestGeyser(0, 0);
    double minGeyserDistanceFromHome = std::numeric_limits<double>::max();
    CCPosition homePosition = m_bot.GetStartLocation();

    for (auto & unit : m_bot.GetUnits())
    {
        if (!unit.getType().isGeyser())
        {
            continue;
        }

        CCPosition geyserPos(unit.getPosition());

        // check to see if it's next to one of our depots
        bool nearDepot = false;
        for (auto & unit : m_bot.UnitInfo().getUnits(Players::Self))
        {
            if (unit.getType().isResourceDepot() && Util::Dist(unit, geyserPos) < 10)
            {
                nearDepot = true;
            }
        }

        if (nearDepot)
        {
            double homeDistance = Util::Dist(unit, homePosition);

            if (homeDistance < minGeyserDistanceFromHome)
            {
                minGeyserDistanceFromHome = homeDistance;
                closestGeyser = unit.getPosition();
            }
        }
    }

#ifdef SC2API
    return CCTilePosition((int)closestGeyser.x, (int)closestGeyser.y);
#else
    return CCTilePosition(closestGeyser);
#endif
}

bool BuildingPlacer::isReserved(int x, int y) const
{
    int rwidth = (int)m_reserveMap.size();
    int rheight = (int)m_reserveMap[0].size();
    if (x < 0 || y < 0 || x >= rwidth || y >= rheight)
    {
        return false;
    }

    return m_reserveMap[x][y];
}

