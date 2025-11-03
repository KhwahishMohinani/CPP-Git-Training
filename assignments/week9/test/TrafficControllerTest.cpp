#include "TrafficController.h"
#include "MockTrafficLight.h"
#include "MockLane.h"
#include "constants.h"
#include "thread"
#include <gtest/gtest.h>

class TrafficControllerTest : public ::testing::Test
{
protected:
    MockTrafficLight light1, light2;
    MockLane lane1, lane2;
    std::vector<ILane *> lanes;
    TrafficController *controller;

    void SetUp() override
    {
        EXPECT_CALL(lane1, getTrafficLight()).WillRepeatedly(testing::Return(&light1));
        EXPECT_CALL(lane2, getTrafficLight()).WillRepeatedly(testing::Return(&light2));
        EXPECT_CALL(lane1, getName()).WillRepeatedly(testing::Return(NORTH_LABEL));
        EXPECT_CALL(lane2, getName()).WillRepeatedly(testing::Return(SOUTH_LABEL));

        lanes = {&lane1, &lane2};

        controller = new TrafficController(lanes);
    }

    void TearDown() override
    {
        delete controller;
    }
};

TEST_F(TrafficControllerTest, GivenNewController_WhenCreated_ThenGreenIndexIsZero)
{
    EXPECT_EQ(controller->getCurrentGreenIndex(), 0);
}

TEST_F(TrafficControllerTest, GivenVehicleFromNorthAndGreenLight_WhenProcessRequest_ThenMoving)
{
    Vehicle vehicle{TEST_CAR1, NORTH_LABEL, RIGHT};
    EXPECT_CALL(light1, getColor()).WillOnce(testing::Return(GREEN));

    EXPECT_EQ(controller->processRequest(vehicle), MOVING);
}

TEST_F(TrafficControllerTest, GivenVehicleFromNorthAndRedLight_WhenProcessRequest_ThenWaiting)
{
    Vehicle vehicle{TEST_CAR1, NORTH_LABEL, RIGHT};
    EXPECT_CALL(light1, getColor()).WillOnce(testing::Return(RED));

    EXPECT_EQ(controller->processRequest(vehicle), WAITING);
}

TEST_F(TrafficControllerTest, GivenLanes_WhenRunControllerCalled_ThenLightsChangeAndStopWhenRequested)
{
    EXPECT_CALL(light1, setRed()).Times(testing::AtLeast(1));
    EXPECT_CALL(light2, setRed()).Times(testing::AtLeast(1));
    EXPECT_CALL(light1, setGreen()).Times(testing::AtLeast(0));
    EXPECT_CALL(light2, setGreen()).Times(testing::AtLeast(0));

    std::thread controllerThread([&]()
                                 { controller->runController(); });

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    controller->stopController();

    if (controllerThread.joinable())
        controllerThread.join();
}

TEST_F(TrafficControllerTest, GivenVehicleTurningLeft_WhenProcessRequest_ThenMovingEvenOnRed)
{
    Vehicle vehicle{TEST_CAR1, NORTH_LABEL, LEFT};
    EXPECT_CALL(light1, getColor()).WillOnce(testing::Return(RED));

    EXPECT_EQ(controller->processRequest(vehicle), MOVING);
}

TEST_F(TrafficControllerTest, GivenVehicleFromUnknownLane_WhenProcessRequest_ThenInvalid)
{
    Vehicle vehicle{TEST_CAR1, EAST_LABEL, RIGHT};

    EXPECT_EQ(controller->processRequest(vehicle), INVALID);
}
