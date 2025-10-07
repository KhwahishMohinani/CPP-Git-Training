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
    EXPECT_CALL(mdb, login(testing::_, testing::_)) // underscore(_) means any parameter
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(true)); // first call returns true
    // .WillRepeatedly(testing::Return(true)) // use it if you want all calls to return true

    // Act
    int retValue = db.Init("User", "12345678");
    // int retValue2 = db.Init("User", "22345678");
    /*
    when Google Mock has no rule for a call
    Google Mock uses default values for types:
    bool → false
    int → 0
    pointers → nullptr
    So the second call automatically returns false
    */

    // Assert
    EXPECT_EQ(retValue, 1);
    // EXPECT_EQ(retValue2, 1);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}