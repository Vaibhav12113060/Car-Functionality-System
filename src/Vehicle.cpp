#include "Vehicle.hpp"
#include <iostream>
using namespace std;

Vehicle::Vehicle(const Position& start)
    : speed(0), gear(GearStatus::PARK), currentLocation(start) {}

void Vehicle::accelerate(double amount) {
    speed += amount;
    if (speed < 0) speed = 0;  
}

void Vehicle::brake(double amount) {
    speed -= amount;
    if (speed < 0) speed = 0;  
}

void Vehicle::shiftGear(GearStatus newGear) {
    gear = newGear;
}

GearStatus Vehicle::getGearStatus() const {
    return gear;
}

double Vehicle::getSpeed() const {
    return speed;
}

Position Vehicle::getLocation() const {
    return currentLocation;
}

void Vehicle::setDestination(const Position& dest) {
    destination = dest;
}

Position Vehicle::getDestination() const {
    return destination;
}

void Vehicle::drive(double time) {
    double distance = speed * time;
    double remainingDistance = currentLocation.distanceTo(destination) - distance;
    if (remainingDistance < 0) remainingDistance = 0;
    cout << "Remaining distance: " << remainingDistance << " km" << endl;
}

double Vehicle::timeToDestination() const {
    double distance = currentLocation.distanceTo(destination);
    return distance / speed;  
}

bool Vehicle::hasArrived() const {
    return currentLocation.distanceTo(destination) == 0;
}
