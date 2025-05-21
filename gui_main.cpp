
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "external/imgui/imgui.h"
#include "external/imgui/backends/imgui_impl_glfw.h"
#include "external/imgui/backends/imgui_impl_opengl3.h"

#include <iostream>
#include <algorithm>
#include "includes/Vehicle.hpp"
#include "includes/Position.hpp"

using namespace std;
using namespace ImGui;

int main() {
    if (!glfwInit()) {
        cerr << "Could not initialize GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 700, "Vehicle Dashboard", nullptr, nullptr);
    if (!window) {
        cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cerr << "Failed to load OpenGL functions\n";
        return -1;
    }

    CreateContext();
    StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    Vehicle vehicle(Position(19.0760, 72.8777)); // Mumbai
    bool isEngineOn = false;
    float fuelLevel = 0.73f;

    float accelerationValue = 8.0f;
    float brakingValue = 6.5f;
    float simulationDuration = 0.4f;

    float destinationLatitude = 13.0827f;     // Chennai
    float destinationLongitude = 80.2707f;

    const int GEAR_INDEX_DRIVE = 3;

    // Refuel feature variables
    bool showRefuelPanel = false;
    float refuelAmount = 0.0f;  

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        NewFrame();

        SetNextWindowSize(ImVec2(600, 530));
        Begin("Vehicle Control Panel", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        if (Checkbox("Engine Status", &isEngineOn)) {
            cout << (isEngineOn ? "Engine turned on\n" : "Engine turned off\n");
        }

        static int selectedGearIndex = 0;
        const char* gearOptions[] = { "PARK", "REVERSE", "NEUTRAL", "DRIVE" };
        if (Combo("Gear Mode", &selectedGearIndex, gearOptions, IM_ARRAYSIZE(gearOptions))) {
            vehicle.shiftGear(static_cast<GearStatus>(selectedGearIndex));
        }

        if (isEngineOn && selectedGearIndex == GEAR_INDEX_DRIVE && fuelLevel > 0.0f) {
            SliderFloat("Acceleration (km/h)", &accelerationValue, 0.0f, 50.0f);
            if (Button("Accelerate")) {
                vehicle.accelerate(accelerationValue);
                fuelLevel -= 0.007f * accelerationValue;
                fuelLevel = max(0.0f, fuelLevel);
            }

            SliderFloat("Braking (km/h)", &brakingValue, 0.0f, 50.0f);
            if (Button("Brake")) {
                vehicle.brake(brakingValue);
            }
        }

        // Fuel display

        ProgressBar(fuelLevel, ImVec2(0.7f, 20)); SameLine();
        Text("Fuel");
        Text("Fuel Remaining: %.2f%%", fuelLevel * 100.0f);

        // Refuel

        if (Button("Refuel")) {
            showRefuelPanel = !showRefuelPanel;
        }

        if (showRefuelPanel) {
            SliderFloat("Amount to Refill (%)", &refuelAmount, 0.0f, 1.0f);
            if (Button("Confirm Refill")) {
                fuelLevel += refuelAmount;
                fuelLevel = min(fuelLevel, 1.0f);
                refuelAmount = 0.0f;  
                showRefuelPanel = false;
            }
        }

        InputFloat("Destination Latitude", &destinationLatitude);
        InputFloat("Destination Longitude", &destinationLongitude);
        if (Button("Set Destination")) {
            vehicle.setDestination(Position(destinationLatitude, destinationLongitude));
        }

        SliderFloat("Drive Time (hrs)", &simulationDuration, 0.1f, 5.0f);
        if (Button("Drive")) {
            vehicle.drive(simulationDuration);


            if (isEngineOn && selectedGearIndex == GEAR_INDEX_DRIVE) {
                fuelLevel -= 0.025f * simulationDuration;
                fuelLevel = max(0.0f, fuelLevel);
            }
        }

        Position currentPosition = vehicle.getLocation();
        Text("Current Location: %.4f, %.4f", currentPosition.latitude, currentPosition.longitude);
        Text("Estimated Time to Arrival: %.2f hrs", vehicle.getSpeed() > 0 ? vehicle.timeToDestination() : 0.0f);
        Text(vehicle.hasArrived() ? "Status: Arrived" : "Status: On The Way");

        End();

        Render();
        int screenWidth, screenHeight;
        glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
        glViewport(0, 0, screenWidth, screenHeight);
        glClearColor(0.1f, 0.15f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
