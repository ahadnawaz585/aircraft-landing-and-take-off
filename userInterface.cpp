#include "UserInterface.h"
#include "SimulationManager.h"
#include "Aircraft.h"
#include <iostream>

UserInterface::UserInterface() : simulationManager(nullptr) {}

UserInterface::UserInterface(SimulationManager& simManager) : simulationManager(&simManager) {}

void UserInterface::header() {
    system("cls");
    std::cout << R"(                                                            |                                                         )" << std::endl;
    std::cout << R"(                                                      --====|====--                                                       )" << std::endl;
    std::cout << R"(                                                            |                                                             )" << std::endl;
    std::cout << R"(                                                                                                                          )" << std::endl;
    std::cout << R"(                                                        .-"""""-.                                                         )" << std::endl;
    std::cout << R"(                                                      .'_________'.                                                       )" << std::endl;
    std::cout << R"(                                                     /_/_|__|__|_\_\                                                      )" << std::endl;
    std::cout << R"(                                                    ;'-._       _.-';                                                     )" << std::endl;
    std::cout << R"(                               ,--------------------|    `-. .-'    |--------------------,                                )" << std::endl;
    std::cout << R"(                                ``""--..__    ___   ;       '       ;   ___    __..--""``                                 )" << std::endl;
    std::cout << R"(                                          `"-// \\.._\             /_..// \\-"`                                           )" << std::endl;
    std::cout << R"(                                             \\_//    '._       _.'    \\_//                                              )" << std::endl;
    std::cout << R"(                                              `"`        ``---``        `"`                                               )" << std::endl;
    std::cout << std::endl;
}


void UserInterface::displaySimulationStatus() {
    if (simulationManager) {
        std::cout << "Runway Status:\n";
        for (const Runway& runway : simulationManager->getRunways()) {
            std::cout << "Runway " << runway.getCode() << ": " << runwayStatusToString(runway.getStatus()) << "\n";
        }

        std::cout << "\nLanding Queue Size: " << simulationManager->getLandingQueueSize() << "\n";
        std::cout << "Takeoff Queue Size: " << simulationManager->getTakeOffQueueSize() << "\n";

        std::cout << "\nStatistics:\n";
        simulationManager->displayStatistics();
    } else {
        std::cerr << "Error: SimulationManager not set in UserInterface.\n";
    }
}

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

void UserInterface::displayLog(const std::string& log) {
    std::cout << "---------------------------------------------\n";
    std::cout << "Log: " << log << "\n";
    std::cout << "---------------------------------------------\n";
}

void UserInterface::displayAircraftDetails(const Aircraft& aircraft) {
    std::cout << "\nAircraft Details:\n";
    std::cout << aircraft.toString() << "\n";
}

void SimulationManager::displayRunwayStatus(const std::string& runwayCode, const std::string& status) {
    std::cout << "Runway " << runwayCode << ": " << status << std::endl;
}
