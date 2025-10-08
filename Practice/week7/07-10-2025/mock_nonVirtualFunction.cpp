#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class A
{
public:
    void fun()
    {
        std::cout << "fun() of class A\n";
    }
};

class Mock : public A
{
public:
    MOCK_METHOD(void, fun, ());
};

TEST(ATest, nonVirtual)
{
    Mock mock;
    EXPECT_CALL(mock, fun())
        .WillOnce(testing::Invoke([]()
                                  { std::cout << "Fake function\n"; }));
    mock.fun();
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}