#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Math
{
public:
    virtual int sum(int a, int b) { return 7; };
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
    Mock mock;
    for (int i = 7; i > 0; i--)
    {
        EXPECT_CALL(mock, sum(testing::_, testing::_))
            .WillOnce(testing::Return(10 * i));
    }
    mock.sum(1, 4);
    mock.sum(2, 4);

    mock.sum(3, 4);
    mock.sum(4, 4);

    mock.sum(5, 4);
    mock.sum(6, 4);
    mock.sum(9, 4);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/*
GMock found some expectations overused (called more times than expected)
And others never used

Because you called the same function repeatedly with the same matcher sum(_, _), GMock had multiple overlapping expectations that confused it.
*/