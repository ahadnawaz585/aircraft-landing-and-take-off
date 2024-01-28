#pragma once

class Timer {
private:
    int currentTime;

public:
    Timer();
    int getCurrentTime() const;
    void incrementTime(int deltaTime);
    void reset();
};

