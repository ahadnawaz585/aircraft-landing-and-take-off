#include "SimulationManager.h"
#include "UserInterface.h" 

int main() {

    SimulationManager simulationManager;


    UserInterface userInterface(simulationManager);


    simulationManager.runSimulation(60);  


    simulationManager.displayStatistics();

    return 0;
}