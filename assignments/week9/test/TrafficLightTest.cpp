#include "TrafficLight.h"
#include "MockSemaphore.h"
#include "constants.h"
#include <gtest/gtest.h>

class TrafficLightTest : public ::testing::Test
{
protected:
    MockSemaphore *mockSemaphore;
    TrafficLight *trafficLight;

    void SetUp() override
    {
        mockSemaphore = new MockSemaphore();
        trafficLight = new TrafficLight(mockSemaphore);
    }

    void TearDown() override
    {
        delete trafficLight;
        delete mockSemaphore;
    }
};

TEST_F(TrafficLightTest, GivenNewTrafficLight_WhenCreated_ThenColorIsRed)
{
    EXPECT_EQ(trafficLight->getColor(), RED);
}

TEST_F(TrafficLightTest, GivenTrafficLight_WhenSetGreenCalled_ThenColorIsGreenAndSemaphoreSignaled)
{
    EXPECT_CALL(*mockSemaphore, signal()).Times(1);
    trafficLight->setGreen();
    EXPECT_EQ(trafficLight->getColor(), GREEN);
}

TEST_F(TrafficLightTest, GivenTrafficLight_WhenSetRedCalled_ThenColorIsRed)
{
    trafficLight->setGreen();
    trafficLight->setRed();
    EXPECT_EQ(trafficLight->getColor(), RED);
}

TEST_F(TrafficLightTest, GivenTrafficLight_WhenGetSemaphoreCalled_ThenReturnSameSemaphore)
{
    EXPECT_EQ(trafficLight->getSemaphore(), mockSemaphore);
}
