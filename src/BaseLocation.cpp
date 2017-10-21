#include "BaseLocation.h"
#include "Util.h"
#include "CCBot.h"
#include <sstream>
#include <iostream>

const int NearBaseLocationTileDistance = 20;

BaseLocation::BaseLocation(CCBot & bot, int baseID, const std::vector<Unit> & resources)
    : m_bot(bot)
    , m_baseID               (baseID)
    , m_isStartLocation      (false)
    , m_left                 (std::numeric_limits<float>::max())
    , m_right                (std::numeric_limits<float>::lowest())
    , m_top                  (std::numeric_limits<float>::lowest())
    , m_bottom               (std::numeric_limits<float>::max())
{
    m_isPlayerStartLocation[0] = false;
    m_isPlayerStartLocation[1] = false;
    m_isPlayerOccupying[0] = false;
    m_isPlayerOccupying[1] = false;

    float resourceCenterX = 0;
    float resourceCenterY = 0;

    // add each of the resources to its corresponding container
    for (auto resource : resources)
    {
        if (Util::IsMineral(resource))
        {
            m_minerals.push_back(resource);
            m_mineralPositions.push_back(resource.getPosition());

            // add the position of the minerals to the center
            resourceCenterX += resource.getPosition().x;
            resourceCenterY += resource.getPosition().y;
        }
        else
        {
            m_geysers.push_back(resource);
            m_geyserPositions.push_back(resource.getPosition());

            // pull the resource center toward the geyser if it exists
            resourceCenterX += resource.getPosition().x;
            resourceCenterY += resource.getPosition().y;
        }

        // set the limits of the base location bounding box
        float resWidth = 1;
        float resHeight = 0.5;

        m_left   = std::min(m_left,   resource.getPosition().x - resWidth);
        m_right  = std::max(m_right,  resource.getPosition().x + resWidth);
        m_top    = std::max(m_top,    resource.getPosition().y + resHeight);
        m_bottom = std::min(m_bottom, resource.getPosition().y - resHeight);
    }

    // calculate the center of the resources
    size_t numResources = m_minerals.size() + m_geysers.size();

    m_centerOfResources = CCPosition(m_left + (m_right-m_left)/2.0f, m_top + (m_bottom-m_top)/2.0f);

    // compute this BaseLocation's DistanceMap, which will compute the ground distance
    // from the center of its recourses to every other tile on the map
    m_distanceMap = m_bot.Map().getDistanceMap(m_centerOfResources);

    // check to see if this is a start location for the map
    for (auto & pos : m_bot.Observation()->GetGameInfo().enemy_start_locations)
    {
        if (containsPosition(pos))
        {
            m_isStartLocation = true;
            m_depotPosition = pos;
        }
    }
    
    // if this base location position is near our own resource depot, it's our start location
    for (auto & unit : m_bot.GetUnits())
    {
        if (unit.getPlayer() == Players::Self && Util::IsTownHall(unit) && containsPosition(unit.getPosition()))
        {
            m_isPlayerStartLocation[Players::Self] = true;
            m_isStartLocation = true;
            m_isPlayerOccupying[Players::Self] = true;
            break;
        }
    }
    
    // if it's not a start location, we need to calculate the depot position
    if (!isStartLocation())
    {
        // the position of the depot will be the closest spot we can build one from the resource center
        for (auto & tile : getClosestTiles())
        {
            // TODO: m_depotPosition = depot position for this base location
        }
    }
}

// TODO: calculate the actual depot position
const CCPosition & BaseLocation::getDepotPosition() const
{
    return getPosition();
}

void BaseLocation::setPlayerOccupying(CCPlayer player, bool occupying)
{
    m_isPlayerOccupying[player] = occupying;

    // if this base is a start location that's occupied by the enemy, it's that enemy's start location
    if (occupying && player == Players::Enemy && isStartLocation() && m_isPlayerStartLocation[player] == false)
    {
        m_isPlayerStartLocation[player] = true;
    }
}

bool BaseLocation::isInResourceBox(int x, int y) const
{
    return x >= m_left && x < m_right && y < m_top && y >= m_bottom;
}

bool BaseLocation::isOccupiedByPlayer(CCPlayer player) const
{
    return m_isPlayerOccupying.at(player);
}

bool BaseLocation::isExplored() const
{
    return false;
}

bool BaseLocation::isPlayerStartLocation(CCPlayer player) const
{
    return m_isPlayerStartLocation.at(player);
}

bool BaseLocation::containsPosition(const CCPosition & pos) const
{
    if (!m_bot.Map().isValidPosition(pos) || (pos.x == 0 && pos.y == 0))
    {
        return false;
    }

    return getGroundDistance(pos) < NearBaseLocationTileDistance;
}

const std::vector<Unit> & BaseLocation::getGeysers() const
{
    return m_geysers;
}

const std::vector<Unit> & BaseLocation::getMinerals() const
{
    return m_minerals;
}

const CCPosition & BaseLocation::getPosition() const
{
    return m_centerOfResources;
}

int BaseLocation::getGroundDistance(const CCPosition & pos) const
{
    //return Util::Dist(pos, m_centerOfResources);
    return m_distanceMap.getDistance(pos);
}

bool BaseLocation::isStartLocation() const
{
    return m_isStartLocation;
}

const std::vector<CCTilePosition> & BaseLocation::getClosestTiles() const
{
    return m_distanceMap.getSortedTiles();
}

void BaseLocation::draw()
{
    m_bot.Map().drawCircle(m_centerOfResources, 1.0f, CCColor(255, 255, 0));

    std::stringstream ss;
    ss << "BaseLocation: " << m_baseID << "\n";
    ss << "Start Loc:    " << (isStartLocation() ? "true" : "false") << "\n";
    ss << "Minerals:     " << m_mineralPositions.size() << "\n";
    ss << "Geysers:      " << m_geyserPositions.size() << "\n";
    ss << "Occupied By:  ";

    if (isOccupiedByPlayer(Players::Self))
    {
        ss << "Self ";
    }

    if (isOccupiedByPlayer(Players::Enemy))
    {
        ss << "Enemy ";
    }

    m_bot.Map().drawText(CCPosition(m_left, m_top+3), ss.str().c_str());
    m_bot.Map().drawText(CCPosition(m_left, m_bottom), ss.str().c_str());

    // draw the base bounding box
    m_bot.Map().drawBox(m_left, m_top, m_right, m_bottom);

    for (float x=m_left; x < m_right; ++x)
    {
        m_bot.Map().drawLine(x, m_top, x, m_bottom, CCColor(160, 160, 160));
    }

    for (float y=m_bottom; y<m_top; ++y)
    {
        m_bot.Map().drawLine(m_left, y, m_right, y, CCColor(160, 160, 160));
    }

    for (auto & mineralPos : m_mineralPositions)
    {
        m_bot.Map().drawCircle(mineralPos, 1.0f, CCColor(0, 128, 128));
    }

    for (auto & geyserPos : m_geyserPositions)
    {
        m_bot.Map().drawCircle(geyserPos, 1.0f, CCColor(0, 255, 0));
    }

    if (m_isStartLocation)
    {
        m_bot.Map().drawCircle(m_depotPosition, 1.0f, CCColor(255, 0, 0));
    }
    
    float ccWidth = 5;
    float ccHeight = 4;
    CCPosition boxtl = m_depotPosition - CCPosition(ccWidth/2, -ccHeight/2);
    CCPosition boxbr = m_depotPosition + CCPosition(ccWidth/2, -ccHeight/2);

    m_bot.Map().drawBox(boxtl.x, boxtl.y, boxbr.x, boxbr.y, CCColor(255, 0, 0));

    //m_distanceMap.draw(m_bot);
}

bool BaseLocation::isMineralOnly() const
{
    return getGeysers().empty();
}