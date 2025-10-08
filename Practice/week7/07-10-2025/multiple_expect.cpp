#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Math
{
public:
    virtual int sum(int a, int b) = 0;
    virtual int sub(int a, int b) = 0;
    virtual ~Math() {};
};

class Mock : public Math
{
public:
    MOCK_METHOD(int, sum, (int a, int b));
    MOCK_METHOD(int, sub, (int a, int b));
};

TEST(MathmockTest, mockTest)
{
    // When a mock call happens, GMock tries to match expectations in reverse order of declaration.
    Mock mock;
    EXPECT_CALL(mock, sum(testing::_, testing::_))
        .Times(3);

    EXPECT_CALL(mock, sub(6, 7))
        .Times(2);
    EXPECT_CALL(mock, sum(6, 7))
        .Times(2);

    mock.sum(2, 4);
    mock.sum(6, 7);
    mock.sum(6, 7);
    // mock.sum(6, 7); // Fail for the third time even if EXPECT_CALL(mock, sum(testing::_, testing::_)) exists
    mock.sum(9, 4);
    mock.sum(9, 4);

    mock.sub(6, 7);
    mock.sub(6, 7);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}