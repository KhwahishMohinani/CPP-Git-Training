#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class DataBaseConnect
{
public:
    virtual bool login(std::string username, std::string password) = 0;
    virtual bool logout(std::string username) = 0;
    virtual int fetchRecord() = 0;
    virtual ~DataBaseConnect() {};
};

class MockDB : public DataBaseConnect
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
    MockDB mdb;
    MyDataBase db(mdb);
    ON_CALL(mdb, login(testing::_, testing::_)); // EXPECT_CALL is expecting the call, ON_CALL is not expecting the call, but if login is called, it should have this in it

    // Act
    int retValue = 1;

    // Assert
    EXPECT_EQ(retValue, 1);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}