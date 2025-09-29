#include <iostream>
#include <vector>
#include <gtest/gtest.h>

class Stack
{
    std::vector<int> vstack;

public:
    void push(int value)
    {
        vstack.push_back(value);
    }

    int pop()
    {
        if (vstack.size() > 0)
        {
            int value = vstack.back();
            vstack.pop_back();
            return value;
        }
        else
            return -1;
    }

    int size()
    {
        return vstack.size();
    }
};

struct stackTest : public testing::Test
{
    Stack s1;
    void SetUp()
    {
        int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int v : values)
        {
            s1.push(v);
        }
    }
    void TearDown()
    {
    }
};

TEST_F(stackTest, PopTest)
{
    int lastPoppedValue = 10;
    while (lastPoppedValue != 1)
    {
        EXPECT_EQ(s1.pop(), lastPoppedValue--);
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}