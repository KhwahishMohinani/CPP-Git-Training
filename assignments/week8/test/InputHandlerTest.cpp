#include "InputHandler.h"
#include "constants.h"
#include <gtest/gtest.h>

TEST(InputHandlerTest, WhenValidIntStringPassed_ThenReturnsTrueAndSetsValue)
{
    InputHandler inputHandler;
    int value;
    bool success = inputHandler.isValidInt(VALID_INT_STRING, value);
    EXPECT_TRUE(success);
    EXPECT_EQ(value, VALID_INT);
}

TEST(InputHandlerTest, WhenInvalidIntStringPassed_ThenReturnsFalse)
{
    InputHandler inputHandler;
    int value;
    bool success = inputHandler.isValidInt(INVALID_INT, value);
    EXPECT_FALSE(success);
}
