
#pragma once

#include "Aircraft.h"
#include "Runway.h"
#include <vector>
#include "Statistics.h"

class crashHandling {
public:
    static void checkForCrash(Aircraft& aircraft, const std::vector<Runway>& runwayList, Statistics& statistics);
};
