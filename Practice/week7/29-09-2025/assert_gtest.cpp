#include <iostream>
#include <gtest/gtest.h>

TEST(TESTNAME, subTestName)
{
    ASSERT_TRUE(100 == 100); // Treminate if false
    EXPECT_TRUE(100 == 100); // doesn't terminate even if it is false
    std::cout << "TEST CALLED\n";
}

TEST(TESTNAME, subTestName2)
{
    ASSERT_FALSE(100 == 100);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}