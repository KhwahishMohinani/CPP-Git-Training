#ifndef ELEVATOR_CONTROLLER_H
#define ELEVATOR_CONTROLLER_H

#include "IElevatorController.h"
#include <vector>
#include <list>
#include <queue>
#include <mutex>

class ElevatorController : public IElevatorController
{
private:
    std::vector<IElevator *> elevators;

    std::list<ElevatorRequest> upRequests;
    std::list<ElevatorRequest> downRequests;
    std::queue<ElevatorRequest> waitingQueue;

    std::mutex mutex;

    bool canServe(IElevator *elevator, const ElevatorRequest &request);
    int calculateCost(IElevator *elevator, int sourceFloor);
    IElevator *findBestElevator(const ElevatorRequest &request);
    bool assignToElevator(ElevatorRequest &request, std::vector<Assignment> &assignments);
    void processRequestList(std::list<ElevatorRequest> &requests, std::vector<Assignment> &assignments);

public:
    bool addElevator(IElevator *elevator);
    bool addRequest(const ElevatorRequest &request);
    std::vector<Assignment> assignRequests();
    bool isRequestQueueEmpty();
    bool allElevatorsIdle();
};

#endif
