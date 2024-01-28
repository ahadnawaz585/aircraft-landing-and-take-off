#include "Timer.h"

Timer::Timer() : currentTime(0) {}

int Timer::getCurrentTime() const {
    return currentTime;
}

void Timer::incrementTime(int deltaTime) {
    currentTime += deltaTime;
}

void Timer::reset() {
    currentTime = 0;
}
