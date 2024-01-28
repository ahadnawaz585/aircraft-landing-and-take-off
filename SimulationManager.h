#pragma once

#include "Aircraft.h"
#include "Runway.h"
#include "Queue.h"
#include "Statistics.h"
#include "Timer.h"
#include <iostream>

class SimulationManager {
public:
    SimulationManager();
    const std::vector<Runway>& getRunways() const;
    size_t getLandingQueueSize() const;
    size_t getTakeOffQueueSize() const;
    void displayStatistics() const;
    void runSimulation(int simulationTime);
    const Aircraft& getCurrentGeneratedAircraft() const;
    const std::queue<Aircraft>& getAircraftInFlight() const;

private:
    std::vector<Runway> runways;
    Queue landingQueue;
    Queue takeOffQueue;
    Statistics statistics;
    Timer timer;
    void generateAircraft();
    void processAircraft();
    void updateRunwayStatus();
    void updateStatistics();
    void handleLanding();
    void handleTakeOff();
    Runway& assignRunwayForLanding();
    Runway& assignRunwayForTakeOff();
    void logEvent(const std::string& event, bool enableLogging);
};
