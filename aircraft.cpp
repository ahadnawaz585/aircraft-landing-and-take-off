#include "Aircraft.h"

Aircraft::Aircraft(AircraftStatus status, int fuel, int time)
    : IdCodeGenerator(), id(generateID()), code(generateCode("ACR")), status(status), fuelLevel(fuel), airTime(time)
{
}

int Aircraft::getId() const {
    return id;
}

AircraftStatus Aircraft::getStatus() const {
    return status;
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

void Aircraft::setAirTime(int time) {
    airTime = time;
}
