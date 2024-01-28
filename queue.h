#pragma once
#include <queue>
#include "aircraft.h"

struct CompareByFuel
{
    bool operator()(const Aircraft &a1, const Aircraft &a2) const
    {
        return a1.getFuelLevel() > a2.getFuelLevel();
    }
};

class Queue
{
private:
    std::queue<Aircraft> takeOffQueue;
    std::priority_queue<Aircraft, std::vector<Aircraft>, CompareByFuel> landingQueue;

public:
    Queue();

    void enqueueLanding(const Aircraft &aircraft);
    void enqueueTakeOff(const Aircraft &aircraft);

    Aircraft dequeueLanding();
    Aircraft dequeueTakeOff();

    bool isLandingQueueEmpty() const;
    bool isTakeOffQueueEmpty() const;
    bool isEmpty() const;
    Aircraft dequeue();

    size_t landingQueueSize() const;
    size_t takeOffQueueSize() const;
};

