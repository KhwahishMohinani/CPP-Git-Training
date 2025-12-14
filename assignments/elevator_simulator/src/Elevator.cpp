#include "Elevator.h"
#include <climits>
#include <thread>
#include <algorithm>
#include <chrono>

Elevator::Elevator(int id)
    : id(id), currentFloor(0), state(State::Idle), elevatorDirection(ElevatorDirection::None) {}

int Elevator::getId()
{
    return id;
}

int Elevator::getCurrentFloor()
{
    std::lock_guard<std::mutex> lock(mutex);
    return currentFloor;
}

State Elevator::getState()
{
    std::lock_guard<std::mutex> lock(mutex);
    return state;
}

ElevatorDirection Elevator::getElevatorDirection()
{
    std::lock_guard<std::mutex> lock(mutex);
    return elevatorDirection;
}

std::vector<int> Elevator::getStops()
{
    std::lock_guard<std::mutex> lock(mutex);
    return stops;
}

void Elevator::setElevatorDirection(ElevatorDirection dir)
{
    std::lock_guard<std::mutex> lock(mutex);
    elevatorDirection = dir;
}

bool Elevator::addStop(int floor, char direction)
{
    bool success = false;
    if (floor >= MIN_FLOOR && floor <= MAX_FLOOR)
    {
        std::lock_guard<std::mutex> lock(mutex);

        if (std::find(stops.begin(), stops.end(), floor) == stops.end())
        {

            stops.push_back(floor);

            if (direction == 'u')
                std::sort(stops.begin(), stops.end());
            else if (direction == 'd')
                std::sort(stops.begin(), stops.end(), std::greater<int>());

            if (state == State::Idle)
            {
                if (floor > currentFloor)
                {
                    state = State::MovingUp;
                    elevatorDirection = ElevatorDirection::Up;
                }
                else if (floor < currentFloor)
                {
                    state = State::MovingDown;
                    elevatorDirection = ElevatorDirection::Down;
                }
                else
                {
                    state = State::DoorOpen;
                    elevatorDirection = (direction == 'u')
                                            ? ElevatorDirection::Up
                                            : ElevatorDirection::Down;
                }
                stateStartTime = std::chrono::steady_clock::now();
            }

            success = true;
        }
    }
    return success;
}

bool Elevator::handleIdle(int target, int localFloor, const std::chrono::steady_clock::time_point &now)
{
    bool success = false;
    if (target != INT_MIN)
    {

        State newState = (target > localFloor) ? State::MovingUp : (target < localFloor) ? State::MovingDown
                                                                                         : State::DoorOpen;

        std::lock_guard<std::mutex> lock(mutex);
        state = newState;
        stateStartTime = now;

        success = true;
    }
    return success;
}

bool Elevator::handleDoorOpen(const std::chrono::steady_clock::time_point &now)
{
    bool success = false;
    bool doorDone = false;
    {
        std::lock_guard<std::mutex> lock(mutex);
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - stateStartTime).count();
        if (elapsed >= DOOR_OPEN_MS)
            doorDone = true;
    }

    if (doorDone)
    {
        std::lock_guard<std::mutex> lock(mutex);
        stops.erase(std::remove(stops.begin(), stops.end(), currentFloor), stops.end());

        if (stops.empty())
            state = State::Idle;
        else
        {
            int next = stops.front();
            state = (next > currentFloor) ? State::MovingUp : State::MovingDown;
        }

        stateStartTime = now;
        success = true;
    }
    return success;
}

int Elevator::computeNextFloor(State localState, int localFloor)
{
    int newFloor = localFloor;

    if (localState == State::MovingUp)
        newFloor++;
    else if (localState == State::MovingDown)
        newFloor--;

    if (newFloor > MAX_FLOOR)
        newFloor = MAX_FLOOR;
    if (newFloor < MIN_FLOOR)
        newFloor = MIN_FLOOR;

    return newFloor;
}

bool Elevator::handleArrival(State localState, int newFloor, const std::chrono::steady_clock::time_point &now)
{
    bool success = false;

    std::lock_guard<std::mutex> lock(mutex);

    if (newFloor != currentFloor)
    {
        currentFloor = newFloor;
        success = true;

        if (!stops.empty() && currentFloor == stops.front())
        {
            state = State::DoorOpen;
            stateStartTime = now;
        }

        else if ((currentFloor == MAX_FLOOR && localState == State::MovingUp) ||
                 (currentFloor == MIN_FLOOR && localState == State::MovingDown))
        {
            stops.erase(std::remove_if(stops.begin(), stops.end(), [](int floor)
                                       { return floor < MIN_FLOOR || floor > MAX_FLOOR; }),
                        stops.end());

            if (stops.empty())
            {
                state = State::Idle;
            }
            else
            {
                int next = stops.front();
                state = (next > currentFloor) ? State::MovingUp : State::MovingDown;
            }

            stateStartTime = now;
        }
    }
    return success;
}

bool Elevator::step()
{
    bool success = false;
    auto now = std::chrono::steady_clock::now();
    State localState;
    int localFloor;
    int target = INT_MIN;

    {
        std::lock_guard<std::mutex> lock(mutex);
        localState = state;
        localFloor = currentFloor;
        if (!stops.empty())
            target = stops.front();
    }

    if (localState == State::Idle)
    {
        success = handleIdle(target, localFloor, now);
    }

    else if (localState == State::DoorOpen)
    {
        success = handleDoorOpen(now);
    }

    else
    {
        int newFloor = computeNextFloor(localState, localFloor);
        success = handleArrival(localState, newFloor, now);
    }
    return success;
}
