#pragma once

#include "IdCodeGenerator.h"
#include <string>

enum class AircraftStatus
{
    LANDING,
    TAKEOFF,
    IN_AIR
};

class Aircraft : public IdCodeGenerator
{
private:
    int id;
    std::string code;
    AircraftStatus status;
    int fuelLevel;
    int airTime;

public:
    Aircraft(AircraftStatus status, int fuel, int time);

    int getId() const;
    AircraftStatus getStatus() const;
    int getFuelLevel() const;
    int getAirTime() const;
    const std::string &getCode() const;

    void setFuelLevel(int fuel);
    void setAirTime(int time);
};

