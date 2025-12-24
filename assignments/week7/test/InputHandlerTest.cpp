#include <sstream>
#include <iostream>
#include "InputHandler.h"
#include <gtest/gtest.h>

TEST(InputHandlerTest, ValidDouble)
{
    InputHandler inputHandler;
    double value;
    std::istringstream input("7.54");

    bool result = inputHandler.isValidDouble(input, value);

    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(value, 7.54);
}

TEST(InputHandlerTest, InvalidDouble)
{
    InputHandler inputHandler;
    double value;
    std::istringstream input("abc");

    bool result = inputHandler.isValidDouble(input, value);

    EXPECT_FALSE(result);
}

TEST(InputHandlerTest, ValidInt)
{
    InputHandler inputHandler;
    int value;
    bool success = inputHandler.isValidInt("123", value);
    EXPECT_TRUE(success);
    EXPECT_EQ(value, 123);
}

TEST(InputHandlerTest, InvalidInt)
{
    InputHandler inputHandler;
    int value;
    bool success = inputHandler.isValidInt("abc", value);
    EXPECT_FALSE(success);
}

TEST(InputHandlerTest, ValidLong)
{
    InputHandler inputHandler;
    long value;
    bool success = inputHandler.isValidLong("1234567890", value);
    EXPECT_TRUE(success);
    EXPECT_EQ(value, 1234567890);
}

TEST(InputHandlerTest, InvalidLong)
{
    InputHandler inputHandler;
    long value;
    bool success = inputHandler.isValidLong("abc", value);
    EXPECT_FALSE(success);
}
