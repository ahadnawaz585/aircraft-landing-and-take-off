// Statistics.h
#pragma once
#include <chrono>

class Statistics {
private:
    int crashedAircraftCount;
    std::chrono::seconds totalLandingTime;
    std::chrono::seconds totalTakeoffTime;
    int totalFuelAvailable;
    std::chrono::seconds totalLandingWaitTime;
    std::chrono::seconds totalTakeoffWaitTime;
    int landingCount;
    int takeoffCount;
    int totalLandedPlanes;
    int totalTookOffPlanes;

public:
    Statistics();

    void aircraftCrashed();
    void updateLandingTime(std::chrono::seconds time);
    void updateTakeoffTime(std::chrono::seconds time);
    void updateFuelAvailable(int fuel);
    void updateLandingCount();
    void updateTakeoffCount();
    void updateLandingWaitTime(std::chrono::seconds waitTime);
    void updateTakeoffWaitTime(std::chrono::seconds waitTime);

    double getAverageLandingWaitTime() const;
    double getAverageTakeoffWaitTime() const;
    int getCrashedAircraftCount() const;
    int getLandingCount() const;
    int getTakeoffCount() const;
    std::chrono::seconds getTotalLandingTime() const;
    std::chrono::seconds getTotalTakeoffTime() const;
    int getTotalFuelAvailable() const;
    int getTotalLandedPlanes() const;
    int getTotalTookOffPlanes() const;

    void incrementLandedPlanes();
    void incrementTookOffPlanes();
};
