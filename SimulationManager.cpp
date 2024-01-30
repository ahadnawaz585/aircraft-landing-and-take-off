#include "SimulationManager.h"
#include "crashHandling.h"
#include <thread>
#include <random>
#include "UserInterface.h"

SimulationManager::SimulationManager()
    : userInterface(new UserInterface(*this)), logger("simulation_log.txt")
{
    for (int i = 0; i < 5; ++i)
    {
        bool hasPriority = (i < 3);
        runways.push_back(Runway(RunwayStatus::FREE, hasPriority));
    }
}

SimulationManager::~SimulationManager()
{
    delete userInterface;
}

void SimulationManager::runSimulation(int simulationTime)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> aircraftCountDistribution(0, 5);

    while (timer.getCurrentTime() < simulationTime)
    {
        int aircraftCount = aircraftCountDistribution(gen);
        for (int i = 0; i < aircraftCount; ++i)
        {
            generateAircraft();
        }

        processAircraft();
        updateRunwayStatus();
        updateStatistics();
        timer.incrementTime(1);

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        waitThreadsCompletion();
        displaySimulationStats();
    }
}

void SimulationManager::waitThreadsCompletion()
{
    for (auto &thread : threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
    threads.clear();
}

void SimulationManager::generateAircraft()
{
    Aircraft landingAircraft;
    Aircraft takeOffAircraft;

    if (rand() % 2 == 0)
    {
        landingAircraft = Aircraft(AircraftStatus::LANDING, rand() % 100 + 1, rand() % 10 + 1);
        landingQueue.enqueueLanding(landingAircraft);

        std::thread([this, landingAircraft]()
                    {
            std::this_thread::sleep_for(std::chrono::seconds(landingAircraft.getAirTime()));
            generateTakeoffAircraft(landingAircraft);
        })
            .detach();
        logEvent("Landing aircraft generated: " + landingAircraft.toString(), true);
        userInterface->displayAircraftDetails(landingAircraft);
    }
    else
    {
        takeOffAircraft = Aircraft(AircraftStatus::TAKEOFF, rand() % 100 + 1, rand() % 10 + 1);

        std::thread([this, takeOffAircraft]()
                    {
            std::this_thread::sleep_for(std::chrono::seconds(takeOffAircraft.getAirTime()));
            generateTakeoffAircraft(takeOffAircraft); })
            .detach();
        takeOffQueue.enqueueTakeOff(takeOffAircraft);
       // logEvent("Takeoff aircraft generated: " + takeOffAircraft.toString(), true);
        userInterface->displayAircraftDetails(takeOffAircraft);
    }

    logRunwayStatus("Runway Status when Aircraft Generated:");
    for (const Runway &runway : runways)
    {
        logRunwayStatus("Runway " + runway.getCode() + ": " + runwayStatusToString(runway.getStatus()));
    }
    updateStatistics();
    displayStatistics();

}

void SimulationManager::logRunwayStatus(const std::string &runwayStatus)
{
    logger.logEvent(runwayStatus);
}

void SimulationManager::generateTakeoffAircraft(const Aircraft& landingAircraft)
{
    Aircraft nonConstAircraft = landingAircraft;
    nonConstAircraft.refill();

    takeOffQueue.enqueueTakeOff(nonConstAircraft);

    std::thread([this, nonConstAircraft]()
        {
            std::this_thread::sleep_for(std::chrono::seconds(nonConstAircraft.getAirTime()));

            // Get the runway associated with the aircraft
            Runway* assignedRunway = nonConstAircraft.getRunway();

            // Set the runway status to FREE
            assignedRunway->setStatus(RunwayStatus::FREE);

            // Log the event indicating the aircraft is set to fly again and mention the runway
            this->logEvent("Aircraft " + nonConstAircraft.getCode() + " is set to fly again. Runway " + assignedRunway->getCode() + " is now FREE.", true);

            // Update the runway status and display stats
            this->updateRunwayStatus();
            this->displaySimulationStats();
        }).detach();

        userInterface->displayAircraftDetails(nonConstAircraft);
        logEvent("Aircraft " + nonConstAircraft.getCode() + " is set to fly again.", true);
}



void SimulationManager::processAircraft()
{
    handleLanding();
    handleTakeOff();
}

void SimulationManager::updateRunwayStatus()
{
    for (Runway &runway : runways)
    {
        std::priority_queue<Aircraft, std::vector<Aircraft>, CompareByFuel> queueCopy;

        if (runway.getLastOperation() == RunwayOperation::LANDING)
        {
            queueCopy = landingQueue.getLandingQueue();
        }
        else
        {
            queueCopy = takeOffQueue.getTakeOffQueue();
        }

        RunwayStatus status = runway.getStatus();
        RunwayOperation lastOperation = runway.getLastOperation();

        if (status == RunwayStatus::OCCUPIED && lastOperation != RunwayOperation::NONE)
        {
            std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
            std::chrono::seconds elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - runway.getLastChangeTime());

            if (elapsedTime >= std::chrono::minutes(1))
            {
                runway.setStatus(RunwayStatus::FREE);
                runway.setPriority(false);
            }
            else
            {
                while (!queueCopy.empty())
                {
                    Aircraft aircraft = queueCopy.top();
                    queueCopy.pop();

                    if (aircraft.getRunway() == &runway && aircraft.getFuelLevel() <= 0)
                    {
                        crashHandling::checkForCrash(aircraft, runways, statistics);
                    }
                }
            }
        }
    }
}

void SimulationManager::updateStatistics()
{
    statistics.updateStatistics(runways);
}

void SimulationManager::handleLanding()
{
    if (!landingQueue.isLandingQueueEmpty())
    {
        Runway& assignedRunway = assignRunwayForLanding();
        Aircraft landingAircraft;
        landingAircraft.setRunway(&assignedRunway);

        if (assignedRunway.getStatus() == RunwayStatus::FREE)
        {
            landingAircraft = landingQueue.dequeueLanding();
            assignedRunway.incrementPlanesLanded();
            assignedRunway.setStatus(RunwayStatus::OCCUPIED);
            assignedRunway.setPriority(false);

         //   userInterface->displayLog("Aircraft " + landingAircraft.getCode() + " is landing on Runway " + assignedRunway.getCode());
        }
    }
}


void SimulationManager::handleTakeOff()
{
    if (!takeOffQueue.isTakeOffQueueEmpty())
    {
        Runway& assignedRunway = assignRunwayForTakeOff();
        Aircraft takeOffAircraft;
        takeOffAircraft.setRunway(&assignedRunway);

        if (assignedRunway.getStatus() == RunwayStatus::FREE)
        {
            takeOffAircraft = takeOffQueue.dequeueTakeOff();
            assignedRunway.incrementPlanesTakeOff();
            assignedRunway.setStatus(RunwayStatus::OCCUPIED);
            assignedRunway.setPriority(false);

          //  userInterface->displayLog("Aircraft " + takeOffAircraft.getCode() + " is taking off from Runway " + assignedRunway.getCode());
        }
    }
}

Runway &SimulationManager::assignRunwayForLanding()
{
    for (Runway &runway : runways)
    {
        if (runway.getStatus() == RunwayStatus::FREE && runway.hasLandingPriority())
        {
            return runway;
        }
    }

    for (Runway &runway : runways)
    {
        if (runway.getStatus() == RunwayStatus::FREE)
        {
            return runway;
        }
    }

    return runways.front();
}

Runway &SimulationManager::assignRunwayForTakeOff()
{
    for (Runway &runway : runways)
    {
        if (runway.getStatus() == RunwayStatus::FREE)
        {
            return runway;
        }
    }

    return runways.front();
}

void SimulationManager::logEvent(const std::string &event, bool enableLogging)
{
    if (enableLogging)
    {
        std::cout << event << std::endl;
    }
}

unsigned long long SimulationManager::getTakeOffQueueSize() const
{
    return takeOffQueue.takeOffQueueSize();
}

void SimulationManager::displayStatistics() const
{
    int totalLandedPlanes = statistics.getTotalLandedPlanes();
    int crashedPlanes = statistics.getCrashedAircraftCount();
    int totalTookOffPlanes = statistics.getTotalTookOffPlanes();
    std::cout << "Crashed Aircraft Count: " << crashedPlanes << "\n";
    std::cout << "Total Landed Planes: " << totalLandedPlanes << "\n";
    std::cout << "Total Took Off Planes: " << totalTookOffPlanes << "\n";
}

const std::vector<Runway> &SimulationManager::getRunways() const
{
    return runways;
}

size_t SimulationManager::getLandingQueueSize() const
{
    return landingQueue.landingQueueSize();
}

std::string SimulationManager::runwayStatusToString(RunwayStatus status)
{
    switch (status)
    {
    case RunwayStatus::FREE:
        return "FREE";
    case RunwayStatus::OCCUPIED:
        return "OCCUPIED";
    default:
        return "UNKNOWN";
    }
}

void SimulationManager::displaySimulationStats() const
{
    std::cout << "Runway Status:" << std::endl;
    for (const Runway &runway : runways)
    {
        std::cout << "Runway " << runway.getCode() << ": " << runway.getStatusString() << std::endl;
       
    }

    std::cout << "\nLanding Queue Size: " << getLandingQueueSize() << std::endl;
    std::cout << "Takeoff Queue Size: " << getTakeOffQueueSize() << std::endl;

    std::cout << "\nStatistics:" << std::endl;
    std::cout << "Crashed Aircraft Count: " << statistics.getCrashedAircraftCount() << std::endl;
    std::cout << "Total Landed Planes: " << statistics.getTotalLandedPlanes() << std::endl;
    std::cout << "Total Took Off Planes: " << statistics.getTotalTookOffPlanes() << std::endl;
    std::cout << "-----------------------------" << std::endl;
}
