#pragma once

#include "Common.h"
#include "MetaType.h"

class CCBot;

struct BuildOrderItem
{
    MetaType       type;		// the thing we want to 'build'
    int             priority;	// the priority at which to place it in the queue
    bool            blocking;	// whether or not we block further items

    BuildOrderItem(const MetaType & t, int p, bool b);
    bool operator<(const BuildOrderItem & x) const;
};

class BuildOrderQueue
{
    CCBot & m_bot;
    std::deque<BuildOrderItem> m_queue;

    int m_lowestPriority;
    int m_highestPriority;
    int m_defaultPrioritySpacing;
    int m_numSkippedItems;

public:

    BuildOrderQueue(CCBot & bot);

    void clearAll();											// clears the entire build order queue
    void skipItem();											// increments skippedItems
    void queueAsHighestPriority(const MetaType & type, bool blocking);		// queues something at the highest priority
    void queueAsLowestPriority(const MetaType & type, bool blocking);		// queues something at the lowest priority
    void queueItem(const BuildOrderItem & b);			// queues something with a given priority
    void removeHighestPriorityItem();								// removes the highest priority item
    void removeCurrentHighestPriorityItem();

    size_t size();													// returns the size of the queue

    bool isEmpty();
    BuildOrderItem & getHighestPriorityItem();	// returns the highest priority item
    BuildOrderItem & getNextHighestPriorityItem();	// returns the highest priority item

    bool canSkipItem();
    std::string getQueueInformation() const;

    // overload the bracket operator for ease of use
    BuildOrderItem operator [] (int i);
};
