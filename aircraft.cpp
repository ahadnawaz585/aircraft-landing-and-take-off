#include "Aircraft.h"



Aircraft::Aircraft(AircraftStatus status, int fuel, int time)
    : airTime(0), craftStatus(status), fuelLevel(0), id(0) {}


int Aircraft::getId() const {
    return id;
}

AircraftStatus Aircraft::getStatus() const {
    return craftStatus;
}

int Aircraft::getFuelLevel() const {
    return fuelLevel;
}

int Aircraft::getAirTime() const {
    return airTime;
}

const std::string& Aircraft::getCode() const {
    return code;
}

void Aircraft::setFuelLevel(int fuel) {
    fuelLevel = fuel;
}

void Aircraft::setStatus(AircraftStatus status)
{
    craftStatus = status;
}

void Aircraft::setAirTime(int time) {
    airTime = time;
}

Runway* Aircraft::getRunway() const {
    return runway;
}

void Aircraft::setRunway(Runway* craftRunway) {
    runway = craftRunway;
}

