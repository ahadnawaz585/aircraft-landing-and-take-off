
#include "Timer.h"

Timer::Timer() : startTime(std::chrono::steady_clock::now()) {}

int Timer::getCurrentTime() const {
    auto currentTime = std::chrono::steady_clock::now() - startTime;
    return std::chrono::duration_cast<std::chrono::seconds>(currentTime).count();
}

void Timer::incrementTime(int deltaTime) {
    auto deltaTimeInSeconds = std::chrono::seconds(deltaTime);
    startTime += deltaTimeInSeconds;
}