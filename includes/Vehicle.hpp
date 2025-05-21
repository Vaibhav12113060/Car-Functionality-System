#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "Position.hpp"
#include <string>

// GearStatus Enum 
enum class GearStatus { PARK, REVERSE, NEUTRAL, DRIVE };

class Vehicle {
private:
    double speed;
    GearStatus gear; 
    Position currentLocation;
    Position destination;

public:

    Vehicle(const Position& start);
    
    void shiftGear(GearStatus newGear);

    GearStatus getGearStatus() const;

    void accelerate(double amount);
    
    void brake(double amount);
    
    double getSpeed() const;
    
    Position getLocation() const;
    
    void setDestination(const Position& dest);
    
    Position getDestination() const;
    
    void drive(double time); 
    
    double timeToDestination() const;
    
    bool hasArrived() const;
};

#endif
