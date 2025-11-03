#ifndef I_LANE_H
#define I_LANE_H

#include <string>
class ITrafficLight;

class ILane
{
public:
    virtual std::string getName() = 0;
    virtual ITrafficLight *getTrafficLight() = 0;
};

#endif
