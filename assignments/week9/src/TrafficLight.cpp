#include "TrafficLight.h"
#include "Semaphore.h"
#include "constants.h"

TrafficLight::TrafficLight(ISemaphore *semaPhore)
    : color(RED), semaphore(semaPhore)
{
}

void TrafficLight::setGreen()
{
    color = GREEN;
    semaphore->signal();
}

void TrafficLight::setRed()
{
    color = RED;
}

std::string TrafficLight::getColor() const
{
    return color;
}

ISemaphore *TrafficLight::getSemaphore()
{
    return semaphore;
}
