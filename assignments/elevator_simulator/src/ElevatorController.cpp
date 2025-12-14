#include "ElevatorController.h"
#include <climits>
#include <cmath>
#include <thread>
#include <chrono>

bool ElevatorController::addElevator(IElevator *elevator)
{
    bool success = false;
    if (elevator)
    {
        elevators.push_back(elevator);
        success = true;
    }
    return success;
}

bool ElevatorController::addRequest(const ElevatorRequest &request)
{
    bool success = true;

    if (request.direction != 'u' && request.direction != 'd')
        success = false;
    else if (request.source < MIN_FLOOR || request.source > MAX_FLOOR)
        success = false;
    else if (request.destination < MIN_FLOOR || request.destination > MAX_FLOOR)
        success = false;
    else if ((request.direction == 'u' && request.source == MAX_FLOOR) ||
             (request.direction == 'd' && request.source == MIN_FLOOR))
        success = false;

    if (success && request.delay > 0)
        std::this_thread::sleep_for(std::chrono::milliseconds(request.delay));

    if (success)
    {
        std::lock_guard<std::mutex> lock(mutex);

        if (request.direction == 'u')
            upRequests.push_back(request);
        else
            downRequests.push_back(request);
    }

    return success;
}

bool ElevatorController::isRequestQueueEmpty()
{
    std::lock_guard<std::mutex> lock(mutex);
    return upRequests.empty() &&
           downRequests.empty() &&
           waitingQueue.empty();
}

bool ElevatorController::allElevatorsIdle()
{
    bool success = true;
    for (auto elevator : elevators)
    {
        if (elevator->getState() != State::Idle)
            success = false;

        else if (!elevator->getStops().empty())
            success = false;
    }
    return success;
}

std::vector<Assignment> ElevatorController::assignRequests()
{
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<Assignment> assignments;

    processRequestList(upRequests, assignments);
    processRequestList(downRequests, assignments);

    int pendingRequests = waitingQueue.size();
    while (pendingRequests--)
    {
        ElevatorRequest request = waitingQueue.front();
        waitingQueue.pop();

        if (!assignToElevator(request, assignments))
        {
            waitingQueue.push(request);
        }
    }

    return assignments;
}

bool ElevatorController::canServe(IElevator *elevator, const ElevatorRequest &request)
{
    bool canServe = false;

    State state = elevator->getState();
    ElevatorDirection elevatorDirection = elevator->getElevatorDirection();
    int currentFloor = elevator->getCurrentFloor();

    if (state == State::Idle)
    {
        canServe = true;
    }
    else if (state == State::DoorOpen)
    {
        if (elevatorDirection == ElevatorDirection::Up)
            canServe = (request.direction == 'u' && request.source >= currentFloor);
        else if (elevatorDirection == ElevatorDirection::Down)
            canServe = (request.direction == 'd' && request.source <= currentFloor);
        else
            canServe = true;
    }
    else if (state == State::MovingUp)
    {
        canServe = (request.direction == 'u' && request.source >= currentFloor);
    }
    else if (state == State::MovingDown)
    {
        canServe = (request.direction == 'd' && request.source <= currentFloor);
    }

    return canServe;
}

int ElevatorController::calculateCost(IElevator *elevator, int sourceFloor)
{
    return std::abs(elevator->getCurrentFloor() - sourceFloor);
}

void ElevatorController::processRequestList(std::list<ElevatorRequest> &requests, std::vector<Assignment> &assignments)
{
    for (auto iterator = requests.begin(); iterator != requests.end();)
    {
        ElevatorRequest &request = *iterator;

        if (!assignToElevator(request, assignments))
        {
            waitingQueue.push(request);
            iterator = requests.erase(iterator);
            continue;
        }

        iterator = requests.erase(iterator);
    }
}

bool ElevatorController::assignToElevator(ElevatorRequest &request, std::vector<Assignment> &assignments)
{
    bool success = false;
    IElevator *bestElevator = findBestElevator(request);

    if (bestElevator)
    {

        bestElevator->addStop(request.source, request.direction);
        bestElevator->addStop(request.destination, request.direction);

        assignments.push_back({bestElevator->getId(), request});
        success = true;
    }
    return success;
}

IElevator *ElevatorController::findBestElevator(const ElevatorRequest &request)
{
    IElevator *bestElevator = nullptr;
    int bestCost = INT_MAX;

    for (auto *elevator : elevators)
    {
        if (!canServe(elevator, request))
            continue;

        int cost = calculateCost(elevator, request.source);
        if (cost < bestCost)
        {
            bestCost = cost;
            bestElevator = elevator;
        }
    }

    return bestElevator;
}
