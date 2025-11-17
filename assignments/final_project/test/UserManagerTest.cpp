#include "UserManager.h"
#include "MockFileHandler.h"
#include "MockUser.h"
#include "constants.h"
#include <gtest/gtest.h>

class UserManagerTest : public ::testing::Test
{
protected:
    MockFileHandler *mockFileHandler;
    UserManager *userManager;

    void SetUp() override
    {
        mockFileHandler = new MockFileHandler();
        EXPECT_CALL(*mockFileHandler, loadUsers(testing::_));
        userManager = new UserManager(mockFileHandler);
    }

    void TearDown() override
    {
        delete userManager;
        delete mockFileHandler;
    }
};

TEST_F(UserManagerTest, GivenValidDetails_WhenCreatingUser_ThenReturnsNewUser)
{
    IUser *user = userManager->createUser(TEST_USERNAME1, TEST_PASSWORD1, TEST_FULLNAME1);
    EXPECT_NE(user, nullptr);
    delete user;
}

TEST_F(UserManagerTest, GivenEmptyUsername_WhenCreatingUser_ThenReturnsNullptr)
{
    IUser *user = userManager->createUser("", TEST_PASSWORD1, TEST_FULLNAME1);
    EXPECT_EQ(user, nullptr);
}

TEST_F(UserManagerTest, GivenValidUser_WhenAddingUser_ThenUserIsStoredSuccessfully)
{
    MockUser *mockUser = new MockUser();

    EXPECT_CALL(*mockUser, getUsername())
        .WillRepeatedly(::testing::Return(TEST_USERNAME1));

    EXPECT_CALL(*mockFileHandler, saveUsers(testing::_));
    EXPECT_TRUE(userManager->addUser(mockUser));

    delete mockUser;
}

TEST_F(UserManagerTest, GivenNullUser_WhenAddingUser_ThenReturnFalse)
{
    EXPECT_FALSE(userManager->addUser(nullptr));
}

TEST_F(UserManagerTest, GivenDuplicateUsername_WhenAddingUser_ThenAdditionFails)
{
    MockUser *user1 = new MockUser();
    MockUser *user2 = new MockUser();

    EXPECT_CALL(*user1, getUsername()).WillRepeatedly(::testing::Return(TEST_USERNAME2));
    EXPECT_CALL(*user2, getUsername()).WillRepeatedly(::testing::Return(TEST_USERNAME2));

    EXPECT_CALL(*mockFileHandler, saveUsers(testing::_)).Times(1);
    EXPECT_TRUE(userManager->addUser(user1));

    EXPECT_FALSE(userManager->addUser(user2));

    delete user1;
    delete user2;
}

TEST_F(UserManagerTest, GivenValidCredentials_WhenSigningIn_ThenSignInSucceeds)
{
    MockUser *mockUser = new MockUser();
    EXPECT_CALL(*mockUser, getUsername()).WillOnce(::testing::Return(TEST_USERNAME1));
    EXPECT_CALL(*mockUser, getPassword()).WillOnce(::testing::Return(TEST_ENCODED_PASSWORD1));

    EXPECT_CALL(*mockFileHandler, saveUsers(testing::_));
    userManager->addUser(mockUser);

    EXPECT_EQ(userManager->signIn(TEST_USERNAME1, TEST_PASSWORD1), SIGN_IN_SUCCESS);

    delete mockUser;
}

TEST_F(UserManagerTest, GivenNonExistingUsername_WhenSigningIn_ThenReturnInvalidUsername)
{
    EXPECT_EQ(userManager->signIn(TEST_USERNAME1, TEST_PASSWORD1), INVALID_USERNAME);
}

TEST_F(UserManagerTest, GivenValidUsernameButWrongPassword_WhenSigningIn_ThenReturnInvalidPassword)
{
    MockUser *mockUser = new MockUser();
    EXPECT_CALL(*mockUser, getUsername()).WillOnce(::testing::Return(TEST_USERNAME1));
    EXPECT_CALL(*mockUser, getPassword()).WillOnce(::testing::Return(TEST_PASSWORD1));

    EXPECT_CALL(*mockFileHandler, saveUsers(testing::_));
    userManager->addUser(mockUser);

    EXPECT_EQ(userManager->signIn(TEST_USERNAME1, TEST_PASSWORD2), INVALID_PASSWORD);

    delete mockUser;
}

TEST_F(UserManagerTest, GivenExistingUser_WhenGettingUserAccount_ThenReturnUser)
{
    MockUser *mockUser = new MockUser();
    EXPECT_CALL(*mockUser, getUsername()).WillRepeatedly(::testing::Return(TEST_USERNAME1));

    EXPECT_CALL(*mockFileHandler, saveUsers(testing::_));
    userManager->addUser(mockUser);

    IUser *returnedUser = userManager->getUserAccount(TEST_USERNAME1);
    EXPECT_EQ(returnedUser, mockUser);

    delete mockUser;
}

TEST_F(UserManagerTest, GivenNoUsers_WhenGettingUserAccount_ThenReturnNullptr)
{
    IUser *returnedUser = userManager->getUserAccount(TEST_USERNAME1);
    EXPECT_EQ(returnedUser, nullptr);
}

TEST_F(UserManagerTest, GivenValidUser_WhenEditingProfile_ThenPasswordAndFullNameAreUpdated)
{
    MockUser *mockUser = new MockUser();

    EXPECT_CALL(*mockUser, setPassword(TEST_PASSWORD2)).Times(1);
    EXPECT_CALL(*mockUser, setFullName(TEST_FULLNAME2)).Times(1);
    EXPECT_CALL(*mockFileHandler, saveUsers(testing::_)).Times(1);

    bool result = userManager->editProfile(mockUser, TEST_PASSWORD2, TEST_FULLNAME2);
    EXPECT_TRUE(result);

    delete mockUser;
}

TEST_F(UserManagerTest, GivenValidUser_WhenEditingProfileWithOnlyPassword_ThenOnlyPasswordIsUpdated)
{
    MockUser *mockUser = new MockUser();

    EXPECT_CALL(*mockUser, setPassword(TEST_PASSWORD2)).Times(1);
    EXPECT_CALL(*mockUser, setFullName(testing::_)).Times(0);
    EXPECT_CALL(*mockFileHandler, saveUsers(testing::_)).Times(1);

    bool result = userManager->editProfile(mockUser, TEST_PASSWORD2, "");
    EXPECT_TRUE(result);

    delete mockUser;
}

TEST_F(UserManagerTest, GivenValidUser_WhenEditingProfileWithOnlyFullName_ThenOnlyFullNameIsUpdated)
{
    MockUser *mockUser = new MockUser();

    EXPECT_CALL(*mockUser, setPassword(testing::_)).Times(0);
    EXPECT_CALL(*mockUser, setFullName(TEST_FULLNAME2)).Times(1);
    EXPECT_CALL(*mockFileHandler, saveUsers(testing::_)).Times(1);

    bool result = userManager->editProfile(mockUser, "", TEST_FULLNAME2);
    EXPECT_TRUE(result);

    delete mockUser;
}

TEST_F(UserManagerTest, GivenNullUser_WhenEditingProfile_ThenReturnsFalse)
{
    EXPECT_FALSE(userManager->editProfile(nullptr, TEST_PASSWORD2, TEST_FULLNAME2));
}

TEST_F(UserManagerTest, GivenValidUser_WhenDeletingUser_ThenReturnsTrue)
{
    MockUser *mockUser = new MockUser();

    bool result = userManager->deleteUser(mockUser);
    EXPECT_TRUE(result);
}

TEST_F(UserManagerTest, GivenNullUser_WhenDeletingUser_ThenReturnsFalse)
{
    bool result = userManager->deleteUser(nullptr);
    EXPECT_FALSE(result);
}

TEST_F(UserManagerTest, GivenExistingUser_WhenRemovingUserByUsername_ThenUserIsRemovedAndReturnsTrue)
{
    MockUser *mockUser = new MockUser();
    EXPECT_CALL(*mockUser, getUsername()).WillRepeatedly(::testing::Return(TEST_USERNAME1));

    EXPECT_CALL(*mockFileHandler, saveUsers(testing::_)).Times(2);
    userManager->addUser(mockUser);

    bool result = userManager->removeUser(TEST_USERNAME1);
    EXPECT_TRUE(result);

    EXPECT_EQ(userManager->getUserAccount(TEST_USERNAME1), nullptr);

    delete mockUser;
}

TEST_F(UserManagerTest, GivenNonExistentUser_WhenRemovingUserByUsername_ThenReturnsFalse)
{
    bool result = userManager->removeUser(TEST_USERNAME1);
    EXPECT_FALSE(result);
}

TEST_F(UserManagerTest, GivenMultipleUsers_WhenDeletingAllUsers_ThenAllUsersAreRemoved)
{
    MockUser *user1 = new MockUser();
    MockUser *user2 = new MockUser();

    EXPECT_CALL(*user1, getUsername()).WillRepeatedly(::testing::Return(TEST_USERNAME1));
    EXPECT_CALL(*user2, getUsername()).WillRepeatedly(::testing::Return(TEST_USERNAME2));

    EXPECT_CALL(*mockFileHandler, saveUsers(testing::_)).Times(2);
    userManager->addUser(user1);
    userManager->addUser(user2);

    userManager->deleteAllUsers();

    EXPECT_EQ(userManager->getUserAccount(TEST_USERNAME1), nullptr);
    EXPECT_EQ(userManager->getUserAccount(TEST_USERNAME2), nullptr);

    delete user1;
    delete user2;
}
