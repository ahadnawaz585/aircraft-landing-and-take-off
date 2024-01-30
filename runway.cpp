// Runway.cpp
#include "Runway.h"

Runway::Runway(RunwayStatus status, bool priority)
    : IdCodeGenerator(), id(generateID()), code(generateCode("RW")), status(status), lastOperation(RunwayOperation::LANDING),
    hasPriority(priority), planesLanded(0), planesTakeOff(0) {}

RunwayStatus Runway::getStatus() const
{
    return status;
}

bool Runway::hasLandingPriority() const
{
    return hasPriority;
}

int Runway::getPlanesLanded() const
{
    return planesLanded;
}

int Runway::getPlanesTakeOff() const
{
    return planesTakeOff;
}

const std::string& Runway::getCode() const
{
    return code;
}

void Runway::setStatus(RunwayStatus status)
{
    this->status = status;
}

void Runway::setPriority(bool priority)
{
    this->hasPriority = priority;
}

std::string Runway::getStatusString() const {
    switch (status) {
    case RunwayStatus::FREE:
        return "FREE";
    case RunwayStatus::OCCUPIED:
        return "OCCUPIED";
    default:
        return "UNKNOWN";
    }
}

void Runway::incrementPlanesLanded()
{
    planesLanded++;
    lastOperation = RunwayOperation::LANDING;
    lastChangeTime = std::chrono::steady_clock::now();
}

void Runway::incrementPlanesTakeOff()
{
    planesTakeOff++;
    lastOperation = RunwayOperation::TAKEOFF;
    lastChangeTime = std::chrono::steady_clock::now();
}

RunwayOperation Runway::getLastOperation() const
{
    return lastOperation;
}

std::chrono::steady_clock::time_point Runway::getLastChangeTime() const
{
    return lastChangeTime;
}



