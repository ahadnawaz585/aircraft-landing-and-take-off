// Runway.h
#pragma once

#include "IdCodeGenerator.h"
#include <string>
#include <chrono>

enum class RunwayStatus
{
    OCCUPIED,
    FREE
};

enum class RunwayOperation
{
    LANDING,
    TAKEOFF,
     NONE
};

class Runway : public IdCodeGenerator
{
private:
    int id;
    std::string code;
    RunwayStatus status;
    RunwayOperation lastOperation;
    bool hasPriority;
    int planesLanded;
    int planesTakeOff;
    std::chrono::steady_clock::time_point lastChangeTime;

public:
    Runway(RunwayStatus status, bool priority);
    RunwayStatus getStatus() const;
    bool hasLandingPriority() const;
    int getPlanesLanded() const;
    int getPlanesTakeOff() const;
    std::string getStatusString() const;
    const std::string& getCode() const;

    void setStatus(RunwayStatus status);
    void setPriority(bool priority);
    void incrementPlanesLanded();
    void incrementPlanesTakeOff();

    RunwayOperation getLastOperation() const;
    std::chrono::steady_clock::time_point getLastChangeTime() const;
};

