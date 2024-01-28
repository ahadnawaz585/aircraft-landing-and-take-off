// queue.cpp

#include "queue.h"

Queue::Queue() {
}

void Queue::enqueueLanding(const Aircraft& aircraft) {
    landingQueue.push(aircraft);
}

void Queue::enqueueTakeOff(const Aircraft& aircraft) {
    takeOffQueue.push(aircraft);
}

Aircraft Queue::dequeueLanding() {
    if (!landingQueue.empty()) {
        Aircraft frontAircraft = landingQueue.top();
        landingQueue.pop();
        return frontAircraft;
    }
    else {
        return Aircraft();
    }
}

Aircraft Queue::dequeueTakeOff() {
    if (!isTakeOffQueueEmpty()) {
        Aircraft frontAircraft = takeOffQueue.top();
        takeOffQueue.pop();
        return frontAircraft;
    }
    else {
        return Aircraft();
    }
}

bool Queue::isLandingQueueEmpty() const {
    return landingQueue.empty();
}

bool Queue::isTakeOffQueueEmpty() const {
    return takeOffQueue.empty();
}

size_t Queue::landingQueueSize() const {
    return landingQueue.size();
}

size_t Queue::takeOffQueueSize() const {
    return takeOffQueue.size();
}

bool Queue::isEmpty() const {
    return landingQueue.empty() && takeOffQueue.empty();
}

Aircraft Queue::dequeue() {
    if (!isLandingQueueEmpty()) {
        return dequeueLanding();
    }
    else if (!isTakeOffQueueEmpty()) {
        return dequeueTakeOff();
    }
    else {
        return Aircraft();
    }
}

const std::priority_queue<Aircraft, std::vector<Aircraft>, CompareByFuel>& Queue::getTakeOffQueue() const {
    return takeOffQueue;
}

const std::priority_queue<Aircraft, std::vector<Aircraft>, CompareByFuel>& Queue::getLandingQueue() const {
    return landingQueue;
}
