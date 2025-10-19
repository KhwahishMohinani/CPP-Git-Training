#include "InputHandler.h"
#include <gtest/gtest.h>

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
