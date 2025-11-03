#ifndef MOCK_TRAFFIC_LIGHT_H
#define MOCK_TRAFFIC_LIGHT_H

#include "ITrafficLight.h"
#include <gmock/gmock.h>

class MockTrafficLight : public ITrafficLight
{
public:
    MOCK_METHOD(void, setGreen, ());
    MOCK_METHOD(void, setRed, ());
    MOCK_METHOD(std::string, getColor, (), (const));
    MOCK_METHOD(ISemaphore *, getSemaphore, ());
};

#endif
