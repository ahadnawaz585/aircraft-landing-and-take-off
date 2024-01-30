#include "SimulationManager.h"
#include "UserInterface.h"
#include <stdlib.h>



int main() {
    std::system("color 4e");
    SimulationManager simulationManager;
    UserInterface userInterface(simulationManager);
    userInterface.header();

    int simulationDuration;
    std::cout << "Enter simulation duration (in time units): ";

    while (!(std::cin >> simulationDuration) || simulationDuration <= 0) {
        std::cin.clear();  
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // discard invalid input
        std::cout << "Invalid input. Please enter a positive integer for simulation duration: ";
    }

    simulationManager.runSimulation(simulationDuration);

    userInterface.displaySimulationStatus();

    return 0;
}


