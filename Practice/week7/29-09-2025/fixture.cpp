#include <iostream>
#include <gtest/gtest.h>

class MyClass
{
    int number;

public:
    MyClass(int num) : number(num) {}
    void Increment()
    {
        number++;
    }
    int getNumber()
    {
        return number;
    }
};

struct MyClassTest : public testing::Test
{
    MyClass *m;
    void SetUp() // SetUp and TearDown (with capital S and T) because they override virtual functions in testing::Test
    {
        m = new MyClass(300);
    }
    void TearDown()
    {
        delete m;
        m = nullptr;
    }
};

TEST_F(MyClassTest, Increment)
{
    // Act
    m->Increment();
    // Assert
    ASSERT_EQ(m->getNumber(), 301);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}