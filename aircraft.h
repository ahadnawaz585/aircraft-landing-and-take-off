
#pragma once

#include "IdCodeGenerator.h"
#include "Runway.h"
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
    AircraftStatus craftStatus = AircraftStatus::IDLE;
    int fuelLevel = 0;
    int airTime = 0;

public:
    Runway* runway = nullptr;
    Runway* getRunway() const;
    Aircraft() = default;
    Aircraft(AircraftStatus status, int fuel, int time);
    std::string toString() const;

    // Getter methods
    int getId() const;
    AircraftStatus getStatus() const;
    int getFuelLevel() const;
    int getAirTime() const;
    const std::string& getCode() const;

    // Setter methods
    void setRunway(Runway* craftRunway);
    void refill();
    void setFuelLevel(int newFuelLevel);
    void setStatus(AircraftStatus status);
    void setAirTime(int time);
};
