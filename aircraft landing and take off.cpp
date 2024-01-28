#include "SimulationManager.h"
#include "UserInterface.h"

int main() {

    SimulationManager simulationManager;


    UserInterface userInterface(simulationManager);


    simulationManager.runSimulation(10); 


    userInterface.displaySimulationStatus();

    return 0;
}
