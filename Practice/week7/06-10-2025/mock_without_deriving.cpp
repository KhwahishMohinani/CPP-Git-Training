#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class DataBaseConnect
{
public:
    MOCK_METHOD(bool, login, (std::string username, std::string password));
    MOCK_METHOD(bool, logout, (std::string username));
    MOCK_METHOD(int, fetchRecord, ());
};

class MyDataBase
{
    DataBaseConnect &dbc;

public:
    MyDataBase(DataBaseConnect &_dbc)
        : dbc(_dbc) {}
    int Init(std::string username, std::string password)
    {
        if (dbc.login(username, password) != true)
        {
            std::cout << "DB Failure\n";
            return -1;
        }
        else
        {
            std::cout << "DB Success\n";
            return 1;
        }
    }
};

TEST(DBTest, loginTest)
{
    // Arrange
    DataBaseConnect mdb;
    MyDataBase db(mdb);
    EXPECT_CALL(mdb, login(testing::_, testing::_))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(true));

    // Act
    int retValue = db.Init("User", "12345678");

    // Assert
    EXPECT_EQ(retValue, 1);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/*
Old versions of GMock: MOCK_METHOD creates pure virtual methods → class is abstract → cannot instantiate.
New versions of GMock (like what you’re using): MOCK_METHOD generates a concrete implementation → class can be instantiated → your code compiles and runs.

But separating interface + mock is the best practice, especially for larger projects.
*/