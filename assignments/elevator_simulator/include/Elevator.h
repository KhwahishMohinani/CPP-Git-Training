#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "IElevator.h"

class Elevator : public IElevator
{
private:
    int id;
    int currentFloor;
    State state;
    ElevatorDirection elevatorDirection;
    std::vector<int> stops;
    std::mutex mutex;
    std::chrono::steady_clock::time_point stateStartTime;

    bool handleIdle(int target, int localFloor, const std::chrono::steady_clock::time_point &now);
    bool handleDoorOpen(const std::chrono::steady_clock::time_point &now);
    int computeNextFloor(State localState, int localFloor);
    bool handleArrival(State localState, int newFloor, const std::chrono::steady_clock::time_point &now);

public:
    Elevator(int id);
    int getId();
    int getCurrentFloor();
    State getState();
    ElevatorDirection getElevatorDirection();
    std::vector<int> getStops();
    void setElevatorDirection(ElevatorDirection dir);
    bool addStop(int floor, char direction);
    bool step();
};

#endif
