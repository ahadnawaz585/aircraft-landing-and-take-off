#include "SimulationManager.h"
#include <cstdlib>
#include <iostream>
#include "crashHandling.h"

SimulationManager::SimulationManager() {
    for (int i = 0; i < 5; ++i) {
        bool hasPriority = (i < 3);
        runways.push_back(Runway(RunwayStatus::FREE, hasPriority));
    }
}

void SimulationManager::runSimulation(int simulationTime) {
    while (timer.getCurrentTime() < simulationTime) {
        generateAircraft();
        processAircraft();
        updateRunwayStatus();
        updateStatistics();
        timer.incrementTime(1);
    }
}

void SimulationManager::generateAircraft() {
    Aircraft landingAircraft;
    Aircraft takeOffAircraft;

    if (rand() % 2 == 0) {
        landingAircraft = Aircraft(AircraftStatus::LANDING, rand() % 100 + 1, rand() % 10 + 1);
        landingQueue.enqueueLanding(landingAircraft);
        logEvent("Landing aircraft generated: " + landingAircraft.toString(), false);
    }
    else {
        takeOffAircraft = Aircraft(AircraftStatus::TAKEOFF, rand() % 100 + 1, rand() % 10 + 1);
        takeOffQueue.enqueueTakeOff(takeOffAircraft);
        logEvent("Takeoff aircraft generated: " + takeOffAircraft.toString(), false);
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
            landingAircraft = landingQueue.dequeueLanding();
            assignedRunway.incrementPlanesLanded();
            assignedRunway.setStatus(RunwayStatus::OCCUPIED);
            assignedRunway.setPriority(false);
            logEvent("Aircraft " + landingAircraft.getCode() + " is landing on Runway " + assignedRunway.getCode(), true);
            
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
            logEvent("Aircraft " + takeOffAircraft.getCode() + " is taking off from Runway " + assignedRunway.getCode(), true);
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

void SimulationManager::logEvent(const std::string& event, bool enableLogging) {
    if (enableLogging) {
        std::cout << event << std::endl;
    }
}

unsigned long long SimulationManager::getTakeOffQueueSize() const {
    return takeOffQueue.takeOffQueueSize(); 
}

void SimulationManager::displayStatistics() const {
    int totalLandedPlanes = statistics.getTotalLandedPlanes();
    int crashedPlanes = statistics.getCrashedAircraftCount();
    int totalTookOffPlanes = statistics.getTotalTookOffPlanes();
    std::cout << "Crashed Aircraft Count: " << crashedPlanes << "\n";
    std::cout << "Total Landed Planes: " << totalLandedPlanes << "\n";
    std::cout << "Total Took Off Planes: " << totalTookOffPlanes << "\n";
}

unsigned long long SimulationManager::getLandingQueueSize() const {
    return landingQueue.landingQueueSize();
}

const std::vector<Runway>& SimulationManager::getRunways() const {
    return runways;
}





