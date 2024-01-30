#include "Aircraft.h"

Runway* Aircraft::getRunway() const {
    return runway;
}

Aircraft::Aircraft(AircraftStatus status, int fuel, int time)
    : IdCodeGenerator(), id(generateID()), code(generateCode("AC")), craftStatus(status), fuelLevel(fuel), airTime(time) {}

std::string Aircraft::toString() const {
    std::string statusString;
    switch (craftStatus) {
    case AircraftStatus::LANDING:
        statusString = "LANDING";
        break;
    case AircraftStatus::TAKEOFF:
        statusString = "TAKEOFF";
        break;
    case AircraftStatus::CRASHED:
        statusString = "CRASHED";
        break;
    case AircraftStatus::IN_AIR:
        statusString = "IN_AIR";
        break;
    case AircraftStatus::IDLE:
        statusString = "IDLE";
        break;
    default:
        statusString = "UNKNOWN";
    }

    std::string runwayInfo;
    if (runway != nullptr) {
        runwayInfo = ", Assigned Runway: " + runway->getCode();
    }

    return "Aircraft " + code + ": Status - " + statusString + ", Fuel - " + std::to_string(fuelLevel) + ", AirTime - " + std::to_string(airTime) + runwayInfo;
}


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

void Aircraft::setRunway(Runway* craftRunway) {
    runway = craftRunway;
}

void Aircraft::setFuelLevel(int newFuelLevel) {
    fuelLevel = newFuelLevel;
}

void Aircraft::setStatus(AircraftStatus status) {
    craftStatus = status;
}

void Aircraft::setAirTime(int time) {
    airTime = time;
}

void Aircraft::refill(){
    setAirTime(0);
    setFuelLevel(100);
    setStatus(AircraftStatus::TAKEOFF);
}