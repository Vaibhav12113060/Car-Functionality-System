#define CATCH_CONFIG_MAIN  
#include "../includes/catch_amalgamated.hpp"
#include "../includes/Vehicle.hpp"
#include "../includes/Position.hpp"

TEST_CASE("Gear shifting functionality") {
    Position start(0.0, 0.0);
    Vehicle car(start);

    car.shiftGear(GearStatus::DRIVE);
    REQUIRE(car.getGearStatus() == GearStatus::DRIVE);

    car.shiftGear(GearStatus::PARK);
    REQUIRE(car.getGearStatus() == GearStatus::PARK);
}

TEST_CASE("Distance calculation between two positions") {
    Position pos1(11.11, 22.22);
    Position pos2(33.33, 44.44);
    double distance = pos1.distanceTo(pos2);
    REQUIRE(distance > 3300.0);
    REQUIRE(distance < 3400.0);
}

TEST_CASE("Vehicle acceleration and braking") {
    Position start(0.0, 0.0);
    Vehicle car(start);

    car.accelerate(85);
    REQUIRE(car.getSpeed() == 85);

    car.brake(35);
    REQUIRE(car.getSpeed() == 50);
}

TEST_CASE("Arrival detection at destination") {
    Position point(10.0, 20.0);
    Vehicle car(point);
    car.setDestination(point);
    REQUIRE(car.hasArrived() == true);
}

TEST_CASE("Time to destination calculation") {
    Position start(12.34, 56.78);
    Position dest(12.34, 57.78); 
    Vehicle car(start);
    car.setDestination(dest);
    car.accelerate(111);  

    double time = car.timeToDestination();
    REQUIRE(time >= 0.9);  
    REQUIRE(time <= 1.1);
}

TEST_CASE("Speed cannot go below zero") {
    Position start(0.0, 0.0);
    Vehicle car(start);

    car.brake(10);  
    REQUIRE(car.getSpeed() == 0);  

    car.accelerate(20);
    car.brake(25);  
    REQUIRE(car.getSpeed() == 0);  
}

TEST_CASE("Vehicle destination setting") {
    Position start(3.3, 4.4);
    Vehicle car(start);

    Position dest(5.5, 6.6);
    car.setDestination(dest);

    REQUIRE(car.getDestination().latitude == 5.5);
    REQUIRE(car.getDestination().longitude == 6.6);
}




///   For Compilation & Run ->    .\run_tests.bat