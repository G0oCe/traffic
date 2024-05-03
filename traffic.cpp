#include <iostream>
#include <mutex>
#include <deque>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

class TrafficController {
private:
    std::mutex mtx;
    int lastDir;
    std::vector<int> onPath;
    std::vector<int> maxLimit;

public:
    TrafficController() : lastDir(0), onPath(4, 0), maxLimit{2, 2, 1, 1} {}

    bool switchLight(int dir) {
        char path = (dir <= 2) ? 'X' : 'Y';
        char lastPath = (lastDir <= 2) ? 'X' : 'Y';

        std::lock_guard<std::mutex> lock(mtx);

        if (path != lastPath) {
            std::cout << "Switch light for path " << path << std::endl;
            lastDir = dir; 
            return true;
        }
        return false;
    }

    void vehicleCrossed(int vehicleId, int dir) {
        char path = (dir <= 2) ? 'X' : 'Y';
        std::lock_guard<std::mutex> lock(mtx); 
        std::cout << "Vehicle " << vehicleId << " crossed path " << path << " in direction " << dir << std::endl;
    }

    void handleVehicles(const std::deque<int>& vehicles, const std::deque<int>& dirs, const std::deque<int>& times) {
        lastDir = dirs[0]; 

        for (size_t i = 0; i < vehicles.size(); i++) {
            if (i > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds((times[i] - times[i - 1]) * 10));
            }

            if (switchLight(dirs[i])) {
                std::fill(onPath.begin(), onPath.end(), 0);
            }

            onPath[dirs[i] - 1]++; 

            vehicleCrossed(vehicles[i], dirs[i]);
        }
    }
};

int main() {
    std::deque<int> vehicles = { 1, 2, 3, 4, 5 };
    std::deque<int> dirs = { 2, 3, 1, 3, 4};
    std::deque<int> times = { 10, 20, 30, 40, 50 };

    TrafficController controller;
    controller.handleVehicles(vehicles, dirs, times);

    return 0;
}
