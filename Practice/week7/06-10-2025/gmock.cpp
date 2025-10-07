#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Sensor
{
public:
    virtual int readCelsius() = 0;
    virtual ~Sensor() {};
};

class MockSensor : public Sensor
{
public:
    MOCK_METHOD(int, readCelsius, ());
};

int getTemperature(Sensor &sensor)
{
    return sensor.readCelsius();
}

TEST(temperatureTest, returnValueFromSensor)
{
    MockSensor mock;
    EXPECT_CALL(mock, readCelsius())
        .WillOnce(testing::Return(30));

    EXPECT_EQ(getTemperature(mock), 30);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}