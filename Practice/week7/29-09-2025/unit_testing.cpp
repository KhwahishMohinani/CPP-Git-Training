#include <iostream>
#include <gtest/gtest.h>

class MyClass
{
    std::string str;
    int num;

public:
    MyClass(std::string s) : str(s) {}
    std::string getStr()
    {
        return str;
    }
    int getNum()
    {
        return num;
    }
};

TEST(Testname, showStrValue)
{
    // Arrange
    MyClass c("root");

    // Act
    std::string value = c.getStr();

    // Assert
    ASSERT_EQ(value, "root");
}

TEST(Testname, showNumValue)
{
    // Arrange
    MyClass c("root");

    // Act
    int value = c.getNum();

    // Assert
    ASSERT_EQ(value, 3);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}