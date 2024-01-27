#pragma once

#include "Aircraft.h"
#include "Runway.h"
#include "Queue.h"
#include "Timer.h"
#include "Statistics.h"
#include <vector>

class SimulationManager {
private:
    std::vector<Aircraft> aircrafts;
    std::vector<Runway> runways;
    Queue landingQueue;
    Queue takeOffQueue;
    Timer timer;
    Statistics statistics;
    int aircraftGenerationInterval;
    int lastAircraftGenerationTime;

public:
    SimulationManager(int numRunways, int generationInterval);

    void generateAircraft();
    void generateAircraftPeriodically();
    void handleArrivalDeparture();
    void updateSimulation(int elapsedTime);
    void printStatistics() const;
};


