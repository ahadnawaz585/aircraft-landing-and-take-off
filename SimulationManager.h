// SimulationManager.h
#pragma once

#include "Aircraft.h"
#include "Runway.h"
#include "Queue.h"
#include "Statistics.h"
#include "Timer.h"

class SimulationManager {
public:
    SimulationManager();

    void runSimulation(int simulationTime);

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
};

