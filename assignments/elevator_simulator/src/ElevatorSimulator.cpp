#include "ElevatorSimulator.h"
#include "ElevatorController.h"
#include "Elevator.h"
#include "constants.h"
#include <iostream>
#include <chrono>

ElevatorSimulator::ElevatorSimulator(const std::string &filename)
    : running(true)
{
    elevators.push_back(new Elevator(0));
    elevators.push_back(new Elevator(1));

    controller = new ElevatorController();

    for (auto elevator : elevators)
        controller->addElevator(elevator);

    fileHandler = new ElevatorRequestFileHandler(filename);
}

ElevatorSimulator::~ElevatorSimulator()
{
    running = false;

    for (auto &thread : threads)
        if (thread.joinable())
            thread.join();

    delete fileHandler;

    delete controller;

    for (auto elevator : elevators)
        delete elevator;
}

void ElevatorSimulator::runInput()
{
    ElevatorRequest request;
    while (fileHandler->readNextRequest(request))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(request.delay));
        controller->addRequest(request);
    }
    {
        std::lock_guard<std::mutex> lock(mutex);
        inputFinished = true;
    }
}

void ElevatorSimulator::printElevatorStatus()
{
    while (running)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        for (auto elevator : elevators)
            elevator->step();

        auto assignments = controller->assignRequests();
        for (auto &assignment : assignments)
        {
            std::cout << ASSIGNED << assignment.request.source
                      << ARROW << assignment.request.destination
                      << TO_ELEVATOR << assignment.elevatorId << "\n";
        }

        std::cout << STATUS;
        for (auto elevator : elevators)
        {
            State state = elevator->getState();
            std::string currentState =
                (state == State::Idle) ? IDLE : (state == State::MovingUp) ? MOVING_UP
                                            : (state == State::MovingDown) ? MOVING_DOWN
                                                                           : DOOR_OPEN;

            std::cout << ELEVATOR_LABEL << elevator->getId()
                      << FLOOR_LABEL << elevator->getCurrentFloor()
                      << STATE_LABEL << currentState;
            auto stops = elevator->getStops();
            std::cout << STOPS_LABEL;
            for (int floor : stops)
                std::cout << floor << " ";
            std::cout << "\n";
        }
        std::cout << SEPARATOR;

        if (inputFinished && controller->isRequestQueueEmpty() && controller->allElevatorsIdle())
        {
            running = false;
        }
    }
}

void ElevatorSimulator::start()
{
    threads.push_back(std::thread(&ElevatorSimulator::runInput, this));

    threads.push_back(std::thread(&ElevatorSimulator::printElevatorStatus, this));

    for (auto &thread : threads)
        if (thread.joinable())
            thread.join();
}
