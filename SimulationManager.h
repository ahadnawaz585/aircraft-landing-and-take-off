#pragma once

#include "Aircraft.h"
#include "Runway.h"
#include "Queue.h"
#include "Statistics.h"
#include <vector>
#include <thread>

#include "Logger.h"
#include "Timer.h"

class UserInterface;

class SimulationManager
{
public:
    SimulationManager();
    ~SimulationManager();
    const std::vector<Runway> &getRunways() const;
    size_t getLandingQueueSize() const;
    size_t getTakeOffQueueSize() const;
    void displayStatistics() const;
    void runSimulation(int simulationTime);
    void displaySimulationStats() const;
    void logRunwayStatus(const std::string &runwayStatus);
    void logEvent(const std::string& event, bool enableLogging);

private:
    Logger logger;
    std::vector<std::thread> threads;
    UserInterface *userInterface;
    std::vector<Runway> runways;
    std::string runwayStatusToString(RunwayStatus status);
    Queue landingQueue;
    Queue takeOffQueue;
    
    Statistics statistics;
    Timer timer;
    void generateAircraft();
    void displayInitialInfo();
    void processAircraft();
    void updateRunwayStatus();
    void updateStatistics();
    void handleLanding();
    void handleTakeOff();
    void displayRunwayStatus(const std::string &runwayCode, const std::string &status);
    void waitThreadsCompletion();
    Runway &assignRunwayForLanding();
    Runway &assignRunwayForTakeOff();
    void generateTakeoffAircraft(const Aircraft& landingAircraft);
};
