#include "SimulationManager.h"
#include <cstdlib>
#include <iostream>

SimulationManager::SimulationManager(int numRunways, int generationInterval)
    : aircraftGenerationInterval(generationInterval), lastAircraftGenerationTime(0) {
    for (int i = 0; i < numRunways; ++i) {
        bool hasPriority = (i < 3);
        runways.push_back(Runway(RunwayStatus::FREE, hasPriority));
    }
}

void SimulationManager::generateAircraft() {
    Aircraft landingAircraft(AircraftStatus::LANDING, rand() % 100, rand() % 10);
    Aircraft takeoffAircraft(AircraftStatus::TAKEOFF, rand() % 100, rand() % 10);

    landingQueue.enqueueLanding(landingAircraft);
    takeOffQueue.enqueueTakeOff(takeoffAircraft);
}

void SimulationManager::generateAircraftPeriodically() {
    int elapsedTimeSinceLastGeneration = static_cast<int>(timer.getCurrentTime() - lastAircraftGenerationTime);
    if (elapsedTimeSinceLastGeneration >= aircraftGenerationInterval) {
        generateAircraft();
        lastAircraftGenerationTime = timer.getCurrentTime();
    }
}

void SimulationManager::handleArrivalDeparture() {
    if (!landingQueue.isLandingQueueEmpty()) {
        for (Runway& runway : runways) {
            if (runway.getStatus() == RunwayStatus::FREE && landingQueue.landingQueueSize() > 0) {
                Aircraft landingAircraft = landingQueue.dequeueLanding();
                runway.setStatus(RunwayStatus::OCCUPIED);
                int landingTime = static_cast<int>(timer.getCurrentTime() - landingAircraft.getAirTime());
                statistics.updateLandingTime(std::chrono::seconds(landingTime));
                std::cout << "Aircraft " << landingAircraft.getCode() << " is landing on Runway "
                    << runway.getCode() << " at time " << timer.getCurrentTime() << std::endl;
                break;
            }
        }
    }

    if (!takeOffQueue.isTakeOffQueueEmpty()) {
        for (Runway& runway : runways) {
            if (runway.getStatus() == RunwayStatus::FREE) {
                Aircraft takeoffAircraft = takeOffQueue.dequeueTakeOff();
                runway.setStatus(RunwayStatus::OCCUPIED);
                int takeoffTime = static_cast<int>(timer.getCurrentTime() - takeoffAircraft.getAirTime());
                statistics.updateTakeoffTime(std::chrono::seconds(takeoffTime));
                std::cout << "Aircraft " << takeoffAircraft.getCode() << " is taking off from Runway "
                    << runway.getCode() << " at time " << timer.getCurrentTime() << std::endl;
                break;
            }
        }
    }
}

void SimulationManager::updateSimulation(int elapsedTime) {
    timer.incrementTime(elapsedTime);
    generateAircraftPeriodically();
    handleArrivalDeparture();

    for (const Aircraft& aircraft : aircrafts) {
        if (aircraft.getStatus() == AircraftStatus::LANDING &&
            static_cast<int>(timer.getCurrentTime() - aircraft.getAirTime()) >= aircraft.getFuelLevel()) {
            statistics.aircraftCrashed();
            std::cout << "Aircraft " << aircraft.getCode() << " has crashed due to low fuel at time "
                << timer.getCurrentTime() << std::endl;
        }
    }

    for (Runway& runway : runways) {
        if (runway.getStatus() == RunwayStatus::OCCUPIED) {
            if (static_cast<int>(timer.getCurrentTime() - runway.getLastChangeTime()) >= 1) {
                runway.setStatus(RunwayStatus::FREE);
                if (runway.getLastOperation() == RunwayOperation::LANDING) {
                    statistics.incrementLandedPlanes();
                }
                else {
                    statistics.incrementTookOffPlanes();
                }
                std::cout << "Runway " << runway.getCode() << " is now free at time "
                    << timer.getCurrentTime() << std::endl;
            }
        }
    }
}

void SimulationManager::printStatistics() const {
    std::cout << "Simulation Statistics:" << std::endl;
    std::cout << "Crashed Aircraft: " << statistics.getCrashedAircraftCount() << std::endl;
    std::cout << "Total Landed Aircraft: " << statistics.getTotalLandedPlanes() << std::endl;
    std::cout << "Total Took Off Aircraft: " << statistics.getTotalTookOffPlanes() << std::endl;
    std::cout << "Average Landing Wait Time: " << statistics.getAverageLandingWaitTime().count() << " seconds"
        << std::endl;
    std::cout << "Average Takeoff Wait Time: " << statistics.getAverageTakeoffWaitTime().count() << " seconds"
        << std::endl;
    std::cout << "Total Fuel Available: " << statistics.getTotalFuelAvailable() << std::endl;
}
