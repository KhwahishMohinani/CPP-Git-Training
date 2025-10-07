#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class DataBaseConnect
{
public:
    virtual bool login(std::string username, std::string password)
    {
        std::cout << "ORIGINAL LOGIN\n";
        return true;
    }
    virtual bool logout(std::string username)
    {
        std::cout << "ORIGINAL LOGOUT\n";
        return true;
    }
    virtual ~DataBaseConnect() {};
};

class MockDB : public DataBaseConnect
{
public:
    MOCK_METHOD(bool, login, (std::string username, std::string password));
    MOCK_METHOD(bool, logout, (std::string username));
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
    DataBaseConnect dbc;
    EXPECT_CALL(mdb, login(testing::_, testing::_))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Invoke(&dbc, &DataBaseConnect::login)); // Invoke needs a pointer to the object, not a copy
    // Invoke(object_pointer, &ClassName::MethodName)

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
Due to invoke
When mdb.login() is called, instead of returning a fake value, actually call the real function DataBaseConnect::login() on the real object dbc
*/
