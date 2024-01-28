
#include "SimulationManager.h"
#include "UserInterface.h"
#include "Logger.h"
#include <iostream>
#include <cstdlib>
#include "crashHandling.h"

SimulationManager::SimulationManager() {

    for (int i = 0; i < 5; ++i) {
        bool hasPriority = (i < 3); 
        runways.push_back(Runway(RunwayStatus::FREE, hasPriority));
    }
}

const std::vector<Runway>& SimulationManager::getRunways() const {
    return runways;
}

size_t SimulationManager::getLandingQueueSize() const {
    return landingQueue.landingQueueSize();
}

size_t SimulationManager::getTakeOffQueueSize() const {
    return takeOffQueue.takeOffQueueSize();
}

void SimulationManager::displayStatistics() const {
    std::cout << "Simulation Statistics:\n";
    std::cout << "-----------------------\n";

    // Access the necessary data members from the statistics object
    // and print them to the console
    std::cout << "Total planes landed: " << statistics.getTotalLandedPlanes() << "\n";
    std::cout << "Total planes took off: " << statistics.getTotalTookOffPlanes() << "\n";
    std::cout << "Average landing time: " << statistics.getAverageLandingWaitTime() << " seconds\n";
    std::cout << "Average takeoff time: " << statistics.getAverageTakeoffWaitTime() << " seconds\n";

    // You can add more statistics based on your requirements

    std::cout << "-----------------------\n";
}

void SimulationManager::runSimulation(int simulationTime) {
    UserInterface ui(*this);
    Logger logger("simulation_log.txt");

    while (timer.getCurrentTime() < simulationTime) {
        generateAircraft();
        processAircraft();
        updateRunwayStatus();
        updateStatistics();

        ui.displaySimulationStatus(); 
        logger.logEvent("Simulation step completed.");

        timer.incrementTime(1);
    }
}

void SimulationManager::generateAircraft() {

    if (rand() % 2 == 0) {
        Aircraft landingAircraft(AircraftStatus::LANDING, rand() % 100 + 1, rand() % 10 + 1);
        landingQueue.enqueueLanding(landingAircraft);
    }
    else {
        Aircraft takeOffAircraft(AircraftStatus::TAKEOFF, rand() % 100 + 1, rand() % 10 + 1);
        takeOffQueue.enqueueTakeOff(takeOffAircraft);
    }
}

void SimulationManager::processAircraft() {
    handleLanding();
    handleTakeOff();
}

void SimulationManager::updateRunwayStatus() {
    for (Runway& runway : runways) {
        std::priority_queue<Aircraft, std::vector<Aircraft>, CompareByFuel> queueCopy;

        if (runway.getLastOperation() == RunwayOperation::LANDING) {
            queueCopy = landingQueue.getLandingQueue();
        }
        else {
            queueCopy = takeOffQueue.getTakeOffQueue();
        }

        RunwayStatus status = runway.getStatus();
        RunwayOperation lastOperation = runway.getLastOperation();

        if (status == RunwayStatus::OCCUPIED && lastOperation != RunwayOperation::NONE) {
            std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
            std::chrono::seconds elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - runway.getLastChangeTime());

            if (elapsedTime >= std::chrono::minutes(1)) {
                runway.setStatus(RunwayStatus::FREE);
                runway.setPriority(false);
            }
            else {
                // Check for fuel exhaustion on occupied runways
                while (!queueCopy.empty()) {
                    Aircraft aircraft = queueCopy.top();
                    queueCopy.pop();

                    if (aircraft.getRunway() == &runway && aircraft.getFuelLevel() <= 0) {
                        // Aircraft has exhausted fuel on occupied runway, trigger crash
                        crashHandling::checkForCrash(aircraft, runways, statistics);
                    }
                }
            }
        }
    }
}


void SimulationManager::updateStatistics() {
    statistics.updateStatistics(runways);
}

void SimulationManager::handleLanding() {
    if (!landingQueue.isLandingQueueEmpty()) {
        Runway& assignedRunway = assignRunwayForLanding();
        Aircraft landingAircraft;
        landingAircraft.setRunway(&assignedRunway);
        if (assignedRunway.getStatus() == RunwayStatus::FREE) {
            Aircraft landingAircraft = landingQueue.dequeueLanding();
            assignedRunway.incrementPlanesLanded();
            assignedRunway.setStatus(RunwayStatus::OCCUPIED);
            assignedRunway.setPriority(false); 

            std::cout << "Aircraft " << landingAircraft.getCode() << " is landing on Runway " << assignedRunway.getCode() << std::endl;
        }
    }
}

void SimulationManager::handleTakeOff() {
    if (!takeOffQueue.isTakeOffQueueEmpty()) {
        Runway& assignedRunway = assignRunwayForTakeOff();
        Aircraft takeOffAircraft;
        takeOffAircraft.setRunway(&assignedRunway);

        if (assignedRunway.getStatus() == RunwayStatus::FREE) {
            takeOffAircraft = takeOffQueue.dequeueTakeOff();
            assignedRunway.incrementPlanesTakeOff();
            assignedRunway.setStatus(RunwayStatus::OCCUPIED);
            assignedRunway.setPriority(false);

            std::cout << "Aircraft " << takeOffAircraft.getCode() << " is taking off from Runway " << assignedRunway.getCode() << std::endl;
        }
    }
}


Runway& SimulationManager::assignRunwayForLanding() {
    for (Runway& runway : runways) {
        if (runway.getStatus() == RunwayStatus::FREE && runway.hasLandingPriority()) {
            return runway;
        }
    }

    for (Runway& runway : runways) {
        if (runway.getStatus() == RunwayStatus::FREE) {
            return runway;
        }
    }


    return runways.front();
}

Runway& SimulationManager::assignRunwayForTakeOff() {

    for (Runway& runway : runways) {
        if (runway.getStatus() == RunwayStatus::FREE) {
            return runway;
        }
    }

    return runways.front();
}
