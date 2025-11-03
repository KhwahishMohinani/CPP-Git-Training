#include "FileHandler.h"
#include "constants.h"
#include <gtest/gtest.h>

class FileHandlerTest : public ::testing::Test
{
protected:
    FileHandler *handler;

    void SetUp() override
    {
        handler = new FileHandler(TEST_FILE_PATH);
    }

    void TearDown() override
    {
        delete handler;
        std::remove(TEST_FILE_PATH.c_str());
    }
};

TEST_F(FileHandlerTest, GivenVehicles_WhenSaveVehiclesToFileCalled_ThenFileIsSavedSuccessfully)
{
    std::vector<Vehicle> vehicles = {
        {TEST_CAR1, NORTH_LABEL, LEFT},
        {TEST_CAR2, SOUTH_LABEL, STRAIGHT},
        {TEST_CAR3, EAST_LABEL, RIGHT}};

    bool result = handler->saveVehiclesToFile(vehicles);
    EXPECT_TRUE(result);
}

TEST(FileHandlerInvalidPathTest, GivenInvalidPath_WhenSaveVehiclesToFileCalled_ThenReturnFalse)
{
    FileHandler badHandler(INVALID_FILE_PATH);
    std::vector<Vehicle> vehicles = {{TEST_CAR1, NORTH_LABEL, LEFT}};

    EXPECT_FALSE(badHandler.saveVehiclesToFile(vehicles));
}

TEST_F(FileHandlerTest, GivenSavedVehicles_WhenLoadVehiclesFromFileCalled_ThenDataMatches)
{
    std::vector<Vehicle> vehicles = {
        {TEST_CAR1, NORTH_LABEL, LEFT},
        {TEST_CAR2, EAST_LABEL, RIGHT}};

    EXPECT_TRUE(handler->saveVehiclesToFile(vehicles));

    std::vector<Vehicle> loaded = handler->loadVehiclesFromFile();

    EXPECT_EQ(loaded, vehicles);
}

TEST_F(FileHandlerTest, GivenEmptyFile_WhenLoadVehiclesFromFileCalled_ThenReturnEmptyVector)
{
    std::vector<Vehicle> vehicles = handler->loadVehiclesFromFile();
    EXPECT_TRUE(vehicles.empty());
}

TEST_F(FileHandlerTest, GivenMissingFile_WhenLoadVehiclesFromFileCalled_ThenReturnEmptyVector)
{
    std::remove(TEST_FILE_PATH.c_str());
    auto vehicles = handler->loadVehiclesFromFile();
    EXPECT_TRUE(vehicles.empty());
}
