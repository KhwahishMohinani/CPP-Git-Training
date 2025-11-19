#include "Lane.h"

Lane::Lane(std::string laneName, ITrafficLight *light)
    : name(laneName), trafficLight(light)
{
}

std::string Lane::getName()
{
    return name;
}

ITrafficLight *Lane::getTrafficLight()
{
    return trafficLight;
}
