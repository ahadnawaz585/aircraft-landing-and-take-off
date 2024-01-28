#pragma once

#include "IdCodeGenerator.h"
#include "runway.h"
#include <string>

enum class AircraftStatus
{
    LANDING,
    TAKEOFF,
    CRASHED,
    IN_AIR,
    IDLE
};

class Aircraft : public IdCodeGenerator
{
private:
    int id;
    std::string code;
    AircraftStatus craftStatus;
    int fuelLevel;
    int airTime;

public:
    Runway* runway = nullptr;
    Runway* getRunway() const;
    Aircraft() = default;
    Aircraft(AircraftStatus status, int fuel, int time);


    int getId() const;
    AircraftStatus getStatus() const;
    int getFuelLevel() const;
    int getAirTime() const;
    const std::string &getCode() const;
    
    void setRunway(Runway* craftRunway);
    void setFuelLevel(int fuel);
    void setStatus(AircraftStatus status);
    void setAirTime(int time);
};

