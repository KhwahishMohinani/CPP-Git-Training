#ifndef I_TRAFFIC_LIGHT_H
#define I_TRAFFIC_LIGHT_H

#include <string>

class ISemaphore;

class ITrafficLight
{
public:
    virtual void setGreen() = 0;
    virtual void setRed() = 0;
    virtual std::string getColor() const = 0;
    virtual ISemaphore *getSemaphore() = 0;
    virtual ~ITrafficLight() {};
};

#endif
