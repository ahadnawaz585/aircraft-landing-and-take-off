#include "Statistics.h"
#include <chrono>
#include "runway.h"
#include "SimulationManager.h"

constexpr std::chrono::seconds operator"" _s(unsigned long long s) {
    return std::chrono::seconds(s);
}

Statistics::Statistics()
    : crashedAircraftCount(0), totalLandingTime(0_s), totalTakeoffTime(0_s), totalFuelAvailable(0),
    landingCount(0), takeoffCount(0), totalLandingWaitTime(0_s), totalTakeoffWaitTime(0_s),
    totalLandedPlanes(0), totalTookOffPlanes(0) {}

void Statistics::aircraftCrashed() {
    crashedAircraftCount++;
}

void Statistics::updateLandingTime(std::chrono::seconds time) {
    totalLandingTime += time;
}

void Statistics::updateTakeoffTime(std::chrono::seconds time) {
    totalTakeoffTime += time;
}

void Statistics::updateFuelAvailable(int fuel) {
    totalFuelAvailable += fuel;
}

void Statistics::updateLandingCount() {
    landingCount++;
}

void Statistics::updateTakeoffCount() {
    takeoffCount++;
}

void Statistics::updateLandingWaitTime(std::chrono::seconds waitTime) {
    totalLandingWaitTime += waitTime;
}

void Statistics::updateTakeoffWaitTime(std::chrono::seconds waitTime) {
    totalTakeoffWaitTime += waitTime;
}

double Statistics::getAverageLandingWaitTime() const {
    return landingCount > 0 ? static_cast<double>(totalLandingWaitTime.count()) / landingCount : 0.0;
}

double Statistics::getAverageTakeoffWaitTime() const {
    return takeoffCount > 0 ? static_cast<double>(totalTakeoffWaitTime.count()) / takeoffCount : 0.0;
}

int Statistics::getCrashedAircraftCount() const {
    return crashedAircraftCount;
}

int Statistics::getLandingCount() const {
    return landingCount;
}

int Statistics::getTakeoffCount() const {
    return takeoffCount;
}

std::chrono::seconds Statistics::getTotalLandingTime() const {
    return totalLandingTime;
}

std::chrono::seconds Statistics::getTotalTakeoffTime() const {
    return totalTakeoffTime;
}

int Statistics::getTotalFuelAvailable() const {
    return totalFuelAvailable;
}

int Statistics::getTotalLandedPlanes() const {
    return totalLandedPlanes;
}

int Statistics::getTotalTookOffPlanes() const {
    return totalTookOffPlanes;
}

void Statistics::incrementLandedPlanes() {
    totalLandedPlanes++;
}

void Statistics::incrementTookOffPlanes() {
    totalTookOffPlanes++;
}

void Statistics::updateStatistics(const std::vector<Runway>& runways) {
    int totalPlanesLanded = 0;
    int totalPlanesTakeOff = 0;
    int totalRunwayOperations = 0;

    for (const Runway& runway : runways) {
        totalPlanesLanded += runway.getPlanesLanded();
        totalPlanesTakeOff += runway.getPlanesTakeOff();

        RunwayStatus status = runway.getStatus();
        RunwayOperation lastOperation = runway.getLastOperation();

        bool isRunwayOccupied = (status == RunwayStatus::OCCUPIED);
        bool hasLandingPriority = runway.hasLandingPriority();

        if (isRunwayOccupied) {
            totalRunwayOperations++;
        }
    }

    double averagePlanesPerRunway = runways.empty() ? 0.0 : static_cast<double>(totalPlanesLanded + totalPlanesTakeOff) / runways.size();


    totalLandedPlanes = totalPlanesLanded;
    totalTookOffPlanes = totalPlanesTakeOff;
    averagePlanesPerRunway = averagePlanesPerRunway;
    totalRunwayOperations = totalRunwayOperations;
}
