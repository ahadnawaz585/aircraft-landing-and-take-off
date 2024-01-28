// queue.h

#pragma once

#include "Aircraft.h"
#include <queue>
#include <functional>

// Custom comparator for priority_queue
struct CompareByFuel {
    bool operator()(const Aircraft& lhs, const Aircraft& rhs) const {
        return lhs.getFuelLevel() < rhs.getFuelLevel();
    }
};

class Queue {
public:
    Queue();

    void enqueueLanding(const Aircraft& aircraft);
    void enqueueTakeOff(const Aircraft& aircraft);

    Aircraft dequeueLanding();
    Aircraft dequeueTakeOff();

    bool isLandingQueueEmpty() const;
    bool isTakeOffQueueEmpty() const;

    size_t landingQueueSize() const;
    size_t takeOffQueueSize() const;

    bool isEmpty() const;
    Aircraft dequeue();

    const std::priority_queue<Aircraft, std::vector<Aircraft>, CompareByFuel>& getTakeOffQueue() const;
    const std::priority_queue<Aircraft, std::vector<Aircraft>, CompareByFuel>& getLandingQueue() const;

private:
    std::priority_queue<Aircraft, std::vector<Aircraft>, CompareByFuel> landingQueue;
    std::priority_queue<Aircraft, std::vector<Aircraft>, CompareByFuel> takeOffQueue;
};
