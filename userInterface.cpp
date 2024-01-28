#include "UserInterface.h"

UserInterface::UserInterface(SimulationManager& simManager) : simulationManager(simManager) {}

std::string UserInterface::runwayStatusToString(RunwayStatus status) {
    switch (status) {
    case RunwayStatus::FREE:
        return "FREE";
    case RunwayStatus::OCCUPIED:
        return "OCCUPIED";
    default:
        return "UNKNOWN";
    }
}

void UserInterface::displaySimulationStatus() {

    std::cout << "Runway Status:\n";
    for (const Runway& runway : simulationManager.getRunways()) {
        std::cout << "Runway " << runway.getCode() << ": " << runwayStatusToString(runway.getStatus()) << "\n";
    }


    std::cout << "\nLanding Queue Size: " << simulationManager.getLandingQueueSize() << "\n";
    std::cout << "Takeoff Queue Size: " << simulationManager.getTakeOffQueueSize() << "\n";


    std::cout << "\nStatistics:\n";
    simulationManager.displayStatistics();
}

void UserInterface::displayLog(const std::string& logMessage) {
    std::cout << "Log: " << logMessage << "\n";
}
