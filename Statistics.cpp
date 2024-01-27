#include "Statistics.h"

Statistics::Statistics()
    : crashedAircraftCount(0), totalLandingTime(std::chrono::seconds(0)), totalTakeoffTime(std::chrono::seconds(0)),
    totalFuelAvailable(0), totalLandingWaitTime(std::chrono::seconds(0)), totalTakeoffWaitTime(std::chrono::seconds(0)),
    landingCount(0), takeoffCount(0) {}

void Statistics::aircraftCrashed() {
    crashedAircraftCount++;
}

void Statistics::updateLandingTime(std::chrono::seconds time) {
    totalLandingTime += time;
    landingCount++;
}

void Statistics::updateTakeoffTime(std::chrono::seconds time) {
    totalTakeoffTime += time;
    takeoffCount++;
}

void Statistics::updateFuelAvailable(int fuel) {
    totalFuelAvailable += fuel;
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
    return landingCount;
}

int Statistics::getTotalTookOffPlanes() const {
    return takeoffCount;
}

void Statistics::incrementLandedPlanes() {
    landingCount++;
}

void Statistics::incrementTookOffPlanes() {
    takeoffCount++;
}