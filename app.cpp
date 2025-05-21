#include <iostream>
using namespace std;
#include "includes/Vehicle.hpp"
#include "includes/Position.hpp"

int main() {
    Position start(37.7749, -122.4194);
    Vehicle car(start);

    int choice;
    bool running = true;

    while (running) {
        cout << "\n--- Car Functionality Menu ---\n";
        cout << "1. Set Destination\n";
        cout << "2. Shift Gear\n";
        cout << "3. Accelerate\n";
        cout << "4. Brake\n";
        cout << "5. Drive\n";
        cout << "6. Show Current Status\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            double lat, lon;
            cout << "Enter latitude and longitude: ";
            cin >> lat >> lon;
            car.setDestination(Position(lat, lon));
            cout << "Destination set.\n";
            break;
        }
        case 2: {
            int gearChoice;
            cout << "Select gear [0-PARK, 1-REVERSE, 2-NEUTRAL, 3-DRIVE]: ";
            cin >> gearChoice;
            car.shiftGear(static_cast<GearStatus>(gearChoice));
            cout << "Gear shifted.\n";
            break;
        }
        case 3: {
            double amount;
            cout << "Enter acceleration amount: ";
            cin >> amount;
            car.accelerate(amount);
            break;
        }
        case 4: {
            double amount;
            cout << "Enter brake amount: ";
            cin >> amount;
            car.brake(amount);
            break;
        }
        case 5: {
            double time;
            cout << "Enter time to drive (in hours): ";
            cin >> time;
            car.drive(time);
            break;
        }
        case 6: {
            cout << "Current speed: " << car.getSpeed() << " km/h\n";
            cout << "Gear: " << static_cast<int>(car.getGearStatus()) << "\n";
            cout << "Time to destination: " << car.timeToDestination() << " hours\n";
            cout << (car.hasArrived() ? "Arrived at destination.\n" : "Still driving...\n");
            break;
        }
        case 7:
            running = false;
            break;
        default:
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}


///  For running app.cpp 
//1.    g++ -Iincludes app.cpp src/Vehicle.cpp src/Position.cpp -o app.exe
//2.    .\app.exe
