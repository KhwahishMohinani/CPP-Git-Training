#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

const char CURRENT_TRAFFIC_LIGHT_STATUS[] = "\n=============================\nCurrent Traffic Light Status:\n";
const char CAR_STATUS[] = "\nCars Status:\n";
const char SEPARATOR[] = "=============================\n";
const char MOVING[] = "Moving";
const char NO_VEHICLES_FOUND[] = "No vehicles found. Exiting...\n";
const char STARTING_SIMULATION[] = "Starting simulation...\n";
const char ALL_VEHICLES_PASSED[] = "All vehicles have passed. Stopping simulation...\n";
const char SIMULATION_STOPPED[] = "Simulation stopped.\n";
const std::string NORTH_LABEL = "North";
const std::string SOUTH_LABEL = "South";
const std::string EAST_LABEL = "East";
const std::string WEST_LABEL = "West";
const std::string WAITING = "Waiting";
const std::string INVALID = "Invalid";
const std::string LEFT = "Left";
const std::string RIGHT = "Right";
const std::string STRAIGHT = "Straight";
const std::string GREEN = "GREEN";
const std::string RED = "RED";
const char FROM[] = " from ";

const std::string FILE_PATH = "data/input.txt";
const std::string TEST_FILE_PATH = "data/test_temp.csv";
const std::string INVALID_FILE_PATH = "/invalid/path/output.csv";

const char TEST_CAR1[] = "Car1";
const char TEST_CAR2[] = "Car2";
const char TEST_CAR3[] = "Car3";

#endif
