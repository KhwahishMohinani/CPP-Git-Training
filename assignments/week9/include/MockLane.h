#ifndef MOCK_LANE_H
#define MOCK_LANE_H

#include "ILane.h"
#include <gmock/gmock.h>

class MockLane : public ILane
{
public:
    MOCK_METHOD(std::string, getName, ());
    MOCK_METHOD(ITrafficLight *, getTrafficLight, ());
};

#endif
