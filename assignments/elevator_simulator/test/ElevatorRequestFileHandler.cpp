#include <gtest/gtest.h>
#include <fstream>
#include "ElevatorRequestFileHandler.h"
#include "constants.h"

class ElevatorRequestFileHandlerTest : public ::testing::Test
{
protected:
    std::string testFile = TEST_FILE_NAME;

    void TearDown() override
    {
        std::remove(testFile.c_str());
    }
};

TEST_F(ElevatorRequestFileHandlerTest, GivenValidRequestLine_WhenReadNextRequestCalled_ThenParsesSuccessfully)
{
    std::ofstream file(testFile);
    file << "1,u,5,100\n";
    file.close();

    ElevatorRequestFileHandler handler(testFile);
    ElevatorRequest request;

    bool result = handler.readNextRequest(request);

    EXPECT_TRUE(result);
    EXPECT_EQ(request.source, 1);
    EXPECT_EQ(request.direction, 'u');
    EXPECT_EQ(request.destination, 5);
    EXPECT_EQ(request.delay, 100);
}

TEST_F(ElevatorRequestFileHandlerTest, GivenEmptyFile_WhenReadNextRequestCalled_ThenReturnsFalse)
{
    std::ofstream file(testFile);
    file << "";
    file.close();

    ElevatorRequestFileHandler handler(testFile);
    ElevatorRequest request;

    EXPECT_FALSE(handler.readNextRequest(request));
}

TEST_F(ElevatorRequestFileHandlerTest, GivenRequestLineWithMissingFields_WhenReadNextRequestCalled_ThenReturnsTrueWithoutCrash)
{
    std::ofstream file(testFile);
    file << "1,u,5\n";
    file.close();

    ElevatorRequestFileHandler handler(testFile);
    ElevatorRequest request{};

    bool result = handler.readNextRequest(request);

    EXPECT_TRUE(result);
}

TEST_F(ElevatorRequestFileHandlerTest, GivenInvalidSourceFloor_WhenReadNextRequestCalled_ThenReturnsTrue)
{
    std::ofstream file(testFile);
    file << "x,u,5,10\n";
    file.close();

    ElevatorRequestFileHandler handler(testFile);
    ElevatorRequest request{};

    EXPECT_TRUE(handler.readNextRequest(request));
}

TEST_F(ElevatorRequestFileHandlerTest, GivenInvalidDestinationFloor_WhenReadNextRequestCalled_ThenReturnsTrue)
{
    std::ofstream file(testFile);
    file << "1,u,y,10\n";
    file.close();

    ElevatorRequestFileHandler handler(testFile);
    ElevatorRequest request{};

    EXPECT_TRUE(handler.readNextRequest(request));
}

TEST_F(ElevatorRequestFileHandlerTest, GivenInvalidDelay_WhenReadNextRequestCalled_ThenReturnsTrue)
{
    std::ofstream file(testFile);
    file << "1,u,5,abc\n";
    file.close();

    ElevatorRequestFileHandler handler(testFile);
    ElevatorRequest request{};

    EXPECT_TRUE(handler.readNextRequest(request));
}

TEST_F(ElevatorRequestFileHandlerTest, GivenMultipleRequestLines_WhenReadNextRequestCalledRepeatedly_ThenReadsSequentially)
{
    std::ofstream file(testFile);
    file << "0,u,3,0\n"
            "5,d,1,50\n";
    file.close();

    ElevatorRequestFileHandler handler(testFile);
    ElevatorRequest request;

    EXPECT_TRUE(handler.readNextRequest(request));
    EXPECT_EQ(request.source, 0);
    EXPECT_EQ(request.direction, 'u');

    EXPECT_TRUE(handler.readNextRequest(request));
    EXPECT_EQ(request.source, 5);
    EXPECT_EQ(request.direction, 'd');

    EXPECT_FALSE(handler.readNextRequest(request));
}
