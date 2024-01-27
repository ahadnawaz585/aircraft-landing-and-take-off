#pragma once
#include <chrono>

class Timer {
private:
    std::chrono::steady_clock::time_point startTime;

public:
    Timer();
    int getCurrentTime() const;
    void incrementTime(int deltaTime);
};