#include "Lane.h"
#include "MockTrafficLight.h"
#include "constants.h"
#include <gtest/gtest.h>

class LaneTest : public ::testing::Test
{
protected:
    MockTrafficLight mockLight;
};

TEST_F(LaneTest, GivenValidInputs_WhenLaneConstructed_ThenGettersReturnExpectedValues)
{
    Lane lane(NORTH_LABEL, &mockLight);

    EXPECT_EQ(lane.getName(), NORTH_LABEL);
    EXPECT_EQ(lane.getTrafficLight(), &mockLight);
}
