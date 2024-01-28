#pragma once

#include "SimulationManager.h"
#include <iostream>

class UserInterface {
public:
    UserInterface(SimulationManager& simManager);
    void displaySimulationStatus();
    void displayLog(const std::string& logMessage);

private:
    SimulationManager& simulationManager;
    std::string runwayStatusToString(RunwayStatus status);
    void displayGeneratedAircraftInfo();
    void displayAircraftInFlight();
};
