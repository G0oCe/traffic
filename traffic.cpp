#include <iostream>
#include <mutex>
#include <deque>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

// TrafficController class to manage the traffic
class TrafficController {
private:
    std::mutex mtx; // Mutex for thread synchronization
    int lastDir; // Last direction of the vehicle
    std::vector<int> onPath; // Number of vehicles on each path
    std::vector<int> maxLimit; // Maximum limit of vehicles on each path

public:
    // Constructor to initialize the variables
    TrafficController() : lastDir(0), onPath(4, 0), maxLimit{2, 2, 1, 1} {}

    // Function to switch the light based on the direction of the vehicle
    bool switchLight(int dir) {
        char path = (dir <= 2) ? 'X' : 'Y';
        char lastPath = (lastDir <= 2) ? 'X' : 'Y';

        std::lock_guard<std::mutex> lock(mtx); // Lock the mutex

        // If the path is not the same as the last path, switch the light
        if (path != lastPath) {
            std::cout << "Switch light for path " << path << std::endl;
            lastDir = dir; 
            return true;
        }
        return false;
    }

    // Function to print the details of the vehicle that crossed the path
    void vehicleCrossed(int vehicleId, int dir) {
        char path = (dir <= 2) ? 'X' : 'Y';
        std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
        std::cout << "Vehicle " << vehicleId << " crossed path " << path << " in direction " << dir << std::endl;
    }

    // Function to handle the vehicles
    void handleVehicles(const std::deque<int>& vehicles, const std::deque<int>& dirs, const std::deque<int>& times) {
        lastDir = dirs[0]; 

        // Loop through all the vehicles
        for (size_t i = 0; i < vehicles.size(); i++) {
            // Sleep for a certain amount of time before processing the next vehicle
            if (i > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds((times[i] - times[i - 1]) * 10));
            }

            // If the light is switched, reset the number of vehicles on each path
            if (switchLight(dirs[i])) {
                std::fill(onPath.begin(), onPath.end(), 0);
            }

            onPath[dirs[i] - 1]++; // Increment the number of vehicles on the current path

            vehicleCrossed(vehicles[i], dirs[i]); // Print the details of the vehicle that crossed the path
        }
    }
};

int main() {
    std::deque<int> vehicles = { 1, 2, 3, 4, 5 }; // IDs of the vehicles
    std::deque<int> dirs = { 2, 3, 1, 3, 4}; // Directions of the vehicles
    std::deque<int> times = { 10, 20, 30, 40, 50 }; // Arrival times of the vehicles

    TrafficController controller; // Create a TrafficController object
    controller.handleVehicles(vehicles, dirs, times); // Handle the vehicles

    return 0; // End of the program
}
