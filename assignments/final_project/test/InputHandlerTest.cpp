#include <gtest/gtest.h>
#include "InputHandler.h"

struct InputTestCase
{
    std::string input;
    bool expectedValid;
    int expectedValue;
};

class InputHandlerParameterizedTest : public ::testing::TestWithParam<InputTestCase>
{
protected:
    InputHandler handler;
};

TEST_P(InputHandlerParameterizedTest, GivenInputString_WhenCheckingValidity_ThenReturnsExpectedResultAndValue)
{
    const auto &parameter = GetParam();
    int value = -1;
    EXPECT_EQ(handler.isValidInt(parameter.input, value), parameter.expectedValid);
    if (parameter.expectedValid)
    {
        EXPECT_EQ(value, parameter.expectedValue);
    }
}

INSTANTIATE_TEST_SUITE_P(
    InputTests,
    InputHandlerParameterizedTest,
    ::testing::Values(
        InputTestCase{"5", true, 5},
        InputTestCase{"12345", true, 12345},
        InputTestCase{"1234567890", true, 1234567890},
        InputTestCase{"", false, -1},
        InputTestCase{"12345678901", false, -1},
        InputTestCase{"12a34", false, -1},
        InputTestCase{"123#45", false, -1},
        InputTestCase{"-123", false, -1},
        InputTestCase{"0", false, -1},
        InputTestCase{"000123", true, 123},
        InputTestCase{"000000", false, -1}));
