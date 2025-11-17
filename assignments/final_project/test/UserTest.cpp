#include "User.h"
#include "constants.h"
#include <gtest/gtest.h>

class UserTest : public ::testing::Test
{
protected:
    User user{TEST_USERNAME1, TEST_PASSWORD1, TEST_FULLNAME1};
};

TEST_F(UserTest, GivenInitializedUser_WhenGettingValues_ThenReturnCorrectData)
{
    EXPECT_EQ(user.getUsername(), TEST_USERNAME1);
    EXPECT_EQ(user.getPassword(), TEST_PASSWORD1);
    EXPECT_EQ(user.getFullName(), TEST_FULLNAME1);
}

TEST_F(UserTest, GivenUser_WhenSettingPassword_ThenPasswordIsUpdated)
{
    user.setPassword(TEST_PASSWORD2);
    EXPECT_EQ(user.getPassword(), TEST_PASSWORD2);
}

TEST_F(UserTest, GivenUser_WhenSettingFullName_ThenFullNameIsUpdated)
{
    user.setFullName(TEST_FULLNAME2);
    EXPECT_EQ(user.getFullName(), TEST_FULLNAME2);
}
