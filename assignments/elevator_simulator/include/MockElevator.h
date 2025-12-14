#ifndef MOCK_ELEVATOR_H
#define MOCK_ELEVATOR_H

#include "IElevator.h"
#include <gmock/gmock.h>

class MockElevator : public IElevator
{
public:
    MOCK_METHOD(int, getId, ());
    MOCK_METHOD(int, getCurrentFloor, ());
    MOCK_METHOD(State, getState, ());
    MOCK_METHOD(ElevatorDirection, getElevatorDirection, ());
    MOCK_METHOD(std::vector<int>, getStops, ());
    MOCK_METHOD(void, setElevatorDirection, (ElevatorDirection dir));
    MOCK_METHOD(bool, addStop, (int floor, char direction));
    MOCK_METHOD(bool, step, ());
};

#endif
