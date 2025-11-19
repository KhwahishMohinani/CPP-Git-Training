#include "TrafficController.h"
#include "ILane.h"
#include "TrafficLight.h"
#include "constants.h"
#include <thread>
#include <chrono>

TrafficController::TrafficController(std::vector<ILane *> &lanesVector)
    : lanes(lanesVector), stop(false), currentGreenIndex(0)
{
}

int TrafficController::getCurrentGreenIndex()
{
    return currentGreenIndex;
}

void TrafficController::stopController()
{
    stop = true;
}

void TrafficController::runController()
{
    if (lanes.empty())
        return;

    while (!stop)
    {
        {
            std::lock_guard<std::mutex> lock(mutex);

            for (size_t i = 0; i < lanes.size(); ++i)
            {
                lanes[i]->getTrafficLight()->setRed();
            }

            lanes[currentGreenIndex]->getTrafficLight()->setGreen();
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));

        {
            std::lock_guard<std::mutex> lock(mutex);
            lanes[currentGreenIndex]->getTrafficLight()->setRed();
            currentGreenIndex = (currentGreenIndex + 1) % lanes.size();
        }
    }
}

std::string TrafficController::processRequest(const Vehicle &vehicle)
{
    for (ILane *lane : lanes)
    {
        if (lane->getName() == vehicle.fromDirection)
        {
            std::string color = lane->getTrafficLight()->getColor();

            if (vehicle.turnDirection == LEFT || color == GREEN)
                return MOVING;
            else
                return WAITING;
        }
    }
    return INVALID;
}
