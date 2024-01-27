#include "queue.h"

Queue::Queue()
{
}

void Queue::enqueueLanding(const Aircraft& aircraft)
{
    landingQueue.push(aircraft);
}

void Queue::enqueueTakeOff(const Aircraft& aircraft)
{
    takeOffQueue.push(aircraft);  
}

Aircraft Queue::dequeueLanding()
{
    Aircraft frontAircraft = landingQueue.top();
    landingQueue.pop();
    return frontAircraft;
}

Aircraft Queue::dequeueTakeOff()
{
    Aircraft frontAircraft = takeOffQueue.front();
    takeOffQueue.pop();
    return frontAircraft;
}

bool Queue::isLandingQueueEmpty() const
{
    return landingQueue.empty();
}

bool Queue::isTakeOffQueueEmpty() const
{
    return takeOffQueue.empty();
}

size_t Queue::landingQueueSize() const
{
    return landingQueue.size();
}

size_t Queue::takeOffQueueSize() const
{
    return takeOffQueue.size();
}
