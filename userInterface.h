#pragma once

#include "SimulationManager.h"
#include "Aircraft.h"
#include <iostream>
#include <string>

class SimulationManager; // Forward declaration

class UserInterface {
public:
    UserInterface(); // New default constructor
    UserInterface(SimulationManager& simManager); // Existing constructor
    void displaySimulationStatus();
    void displayLog(const std::string& log);
    void displayAircraftDetails(const Aircraft& aircraft);
void header();
private:
    SimulationManager* simulationManager; // Pointer instead of reference
    std::string runwayStatusToString(RunwayStatus status);
};
