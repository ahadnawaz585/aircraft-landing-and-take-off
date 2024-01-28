
#include "crashHandling.h"
#include <algorithm>

void crashHandling::checkForCrash(Aircraft& aircraft, const std::vector<Runway>& runwayList, Statistics& statistics)
{
    if (aircraft.getFuelLevel() <= 0 && std::all_of(runwayList.begin(), runwayList.end(), [](const Runway& runway) -> bool {
        return runway.getStatus() == RunwayStatus::OCCUPIED;
        })) {
        aircraft.setStatus(AircraftStatus::CRASHED);
        statistics.aircraftCrashed();
    }
}
