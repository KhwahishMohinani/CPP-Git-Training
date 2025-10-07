#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

void Hello()
{
    std::cout << "Hello\n";
}

class Mock
{
public:
    MOCK_METHOD(void, sayHello, ());
};

TEST(MyTest, InvokeWithoutArguments)
{
    Mock mock;
    EXPECT_CALL(mock, sayHello())
        .WillOnce(testing::Invoke(&Hello));

    mock.sayHello();
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}