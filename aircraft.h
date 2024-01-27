#ifndef AIRCRAFT_H
#define AIRCRAFT_H
#include <string>

enum class AircraftStatus {
    LANDING,
    TAKEOFF,
    IN_AIR
};

class Aircraft {
private:
    int id;
    std::string code;
    AircraftStatus status;
    int fuelLevel;
    int airTime;

    //  auto-incrementing ID
    static int lastAssignedID;
    static int generateID();

    //generating the aircraft code
    static std::string generateCode();

public:
    Aircraft(AircraftStatus status, int fuel, int time);

    int getId() const;
    AircraftStatus getStatus() const;
    int getFuelLevel() const;
    int getAirTime() const;
    const std::string& getCode() const;

    void setFuelLevel(int fuel);
    void setAirTime(int time);
};

#endif // !AIRCRAFT_H
