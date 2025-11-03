#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include "ITrafficLight.h"

class TrafficLight : public ITrafficLight
{
private:
    std::string color;
    ISemaphore *semaphore;

public:
    TrafficLight(ISemaphore *semaPhore);
    void setGreen();
    void setRed();
    std::string getColor() const;
    ISemaphore *getSemaphore();
};

#endif
