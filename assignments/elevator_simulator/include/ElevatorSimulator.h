#ifndef ELEVATOR_SIMULATOR_H
#define ELEVATOR_SIMULATOR_H

#include <vector>
#include <thread>
#include <string>
#include "IElevator.h"
#include "IElevatorController.h"
#include "ElevatorRequestFileHandler.h"

class ElevatorSimulator
{
private:
    std::vector<IElevator *> elevators;
    IElevatorController *controller;
    ElevatorRequestFileHandler *fileHandler;

    std::vector<std::thread> threads;
    std::mutex mutex;

    bool running;
    bool inputFinished = false;

    void runInput();

public:
    ElevatorSimulator(const std::string &filename);
    ~ElevatorSimulator();

    void printElevatorStatus();
    void start();
};

#endif
