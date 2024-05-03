# Traffic Controller

This is a simple C++ program that simulates a traffic controller. The traffic controller manages the flow of vehicles on two paths, 'X' and 'Y', and switches the traffic light based on the direction of the vehicles.

## Features

- Thread-safe operations using `std::mutex`.
- Simulates the arrival of vehicles at different times.
- Switches the traffic light based on the direction of the vehicles.
- Prints the details of the vehicles that crossed the path.

## Usage

1. Compile the program using a C++ compiler (e.g., g++).
2. Run the program. The program will simulate the arrival of vehicles and manage the traffic accordingly.

## Code Structure

- `TrafficController` class: This class manages the traffic. It has the following methods:
  - `switchLight(int dir)`: This method switches the traffic light based on the direction of the vehicle.
  - `vehicleCrossed(int vehicleId, int dir)`: This method prints the details of the vehicle that crossed the path.
  - `handleVehicles(const std::deque<int>& vehicles, const std::deque<int>& dirs, const std::deque<int>& times)`: This method handles the vehicles.

- `main()` function: This function initializes the data and starts the traffic controller.

## Dependencies

- `<iostream>`: For input/output operations.
- `<mutex>`: For thread synchronization.
- `<deque>`: For storing the data of the vehicles.
- `<vector>`: For storing the data of the paths.
- `<string>`: For string operations.
- `<thread>`: For multithreading.
- `<chrono>`: For time-related operations.

