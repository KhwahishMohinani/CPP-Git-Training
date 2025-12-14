#ifndef I_ELEVATOR_H
#define I_ELEVATOR_H

#include <vector>
#include <mutex>
#include <chrono>
#include "constants.h"

class IElevator
{
public:
    virtual int getId() = 0;
    virtual int getCurrentFloor() = 0;
    virtual State getState() = 0;
    virtual ElevatorDirection getElevatorDirection() = 0;
    virtual std::vector<int> getStops() = 0;
    virtual void setElevatorDirection(ElevatorDirection dir) = 0;
    virtual bool addStop(int floor, char direction) = 0;
    virtual bool step() = 0;
};

#endif
