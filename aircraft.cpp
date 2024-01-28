#include "Aircraft.h"
#include "IdCodeGenerator.h"


Aircraft::Aircraft(AircraftStatus status, int fuel, int time)
    : airTime(time), craftStatus(status), fuelLevel(fuel), id(generateID()) {}


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

std::string Aircraft::toString() const
{
    std::string statusString;
    switch (craftStatus)
    {
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
        break;
    }

    return "Aircraft " + code + " Status: " + statusString + " Fuel: " + std::to_string(fuelLevel) +
        " AirTime: " + std::to_string(airTime) + " ID: " + std::to_string(id);
}


