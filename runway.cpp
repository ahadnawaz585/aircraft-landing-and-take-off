#include "Runway.h"

Runway::Runway(RunwayStatus status, bool priority)
    : id(getNextID()), code(generateCode("RW")), status(status), hasPriority(priority), planesLanded(0), planesTakeOff(0) {}

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

const std::string &Runway::getCode() const
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

void Runway::incrementPlanesLanded()
{
    planesLanded++;
}

void Runway::incrementPlanesTakeOff()
{
    planesTakeOff++;
}
