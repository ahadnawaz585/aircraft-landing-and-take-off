#include "aircraft.h"
#include <iostream>
#include <iomanip>
#include <sstream>

int Aircraft::lastAssignedID = 0;

int Aircraft::generateID()
{
    return ++lastAssignedID;
}

std::string Aircraft::generateCode()
{
    std::ostringstream oss;
    oss << "ACR" << std::setw(3) << std::setfill('0') << generateID();
    return oss.str();
}

Aircraft::Aircraft(AircraftStatus status, int fuel, int time)
    : id(generateID()), code(generateCode()), status(status), fuelLevel(fuel), airTime(time) {}

int Aircraft::getId() const
{
    return id;
}

AircraftStatus Aircraft::getStatus() const
{
    return status;
}

int Aircraft::getFuelLevel() const
{
    return fuelLevel;
}

int Aircraft::getAirTime() const
{
    return airTime;
}

const std::string& Aircraft::getCode() const
{
    return code;
}

void Aircraft::setFuelLevel(int fuel)
{
    fuelLevel = fuel;
}

void Aircraft::setAirTime(int time)
{
    airTime = time;
}
