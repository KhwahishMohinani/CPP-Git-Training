#ifndef I_ELEVATOR_CONTROLLER_H
#define I_ELEVATOR_CONTROLLER_H

#include "IElevator.h"
#include "Assignment.h"

class IElevatorController
{
public:
    virtual bool addElevator(IElevator *elevator) = 0;
    virtual bool addRequest(const ElevatorRequest &request) = 0;
    virtual std::vector<Assignment> assignRequests() = 0;
    virtual bool isRequestQueueEmpty() = 0;
    virtual bool allElevatorsIdle() = 0;
};

#endif
