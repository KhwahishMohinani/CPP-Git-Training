#ifndef LANE_H
#define LANE_H

#include "ILane.h"

class Lane : public ILane
{
private:
    std::string name;
    ITrafficLight *trafficLight;

public:
    Lane(std::string laneName, ITrafficLight *light);
    std::string getName();
    ITrafficLight *getTrafficLight();
};

#endif
