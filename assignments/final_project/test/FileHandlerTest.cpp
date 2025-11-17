#include "FileHandler.h"
#include "MockUser.h"
#include "MockPost.h"
#include "constants.h"
#include <gtest/gtest.h>
#include <fstream>
#include <nlohmann/json.hpp>

class FileHandlerTest : public ::testing::Test
{
protected:
    std::string usersFile = TEST_USERS_FILE;
    std::string postsFile = TEST_POSTS_FILE;

    void TearDown()
    {
        std::remove(usersFile.c_str());
        std::remove(postsFile.c_str());
    }
};

TEST_F(FileHandlerTest, GivenMissingUsersFile_WhenLoadingUsers_ThenReturnsFalseAndLeavesMapEmpty)
{
    FileHandler handler(usersFile, postsFile);
    std::unordered_map<std::string, IUser *> users;

    EXPECT_FALSE(handler.loadUsers(users));
    EXPECT_TRUE(users.empty());
}

TEST_F(FileHandlerTest, GivenEmptyUsersFile_WhenLoadingUsers_ThenReturnsTrueAndLoadsNoUsers)
{
    std::ofstream file(usersFile);
    file.close();

    FileHandler handler(usersFile, postsFile);
    std::unordered_map<std::string, IUser *> users;

    EXPECT_TRUE(handler.loadUsers(users));
    EXPECT_TRUE(users.empty());
}

TEST_F(FileHandlerTest, GivenSingleUserInFile_WhenLoadingUsers_ThenLoadsUserCorrectly)
{
    nlohmann::json json = {
        {{USERNAME_LABEL, TEST_USERNAME1}, {PASSWORD_LABEL, TEST_PASSWORD1}, {FULLNAME_LABEL, TEST_FULLNAME1}}};

    std::ofstream file(usersFile);
    file << json;
    file.close();

    FileHandler handler(usersFile, postsFile);
    std::unordered_map<std::string, IUser *> users;

    EXPECT_TRUE(handler.loadUsers(users));
    ASSERT_EQ(users.size(), 1);

    IUser *user = users[TEST_USERNAME1];
    EXPECT_NE(user, nullptr);

    delete user;
}

TEST_F(FileHandlerTest, GivenEmptyUsersMap_WhenSavingUsers_ThenCreatesEmptyJSONArray)
{
    FileHandler handler(usersFile, postsFile);
    std::unordered_map<std::string, IUser *> users;

    EXPECT_TRUE(handler.saveUsers(users));

    std::ifstream file(usersFile);
    ASSERT_TRUE(file.is_open());

    nlohmann::json json;
    file >> json;

    EXPECT_TRUE(json.is_array());
    EXPECT_EQ(json.size(), 0);
}

TEST_F(FileHandlerTest, GivenSingleMockUser_WhenSavingUsers_ThenJSONIsWrittenCorrectly)
{
    MockUser *mockUser = new MockUser();

    EXPECT_CALL(*mockUser, getUsername()).WillRepeatedly(testing::Return(TEST_USERNAME1));
    EXPECT_CALL(*mockUser, getPassword()).WillRepeatedly(testing::Return(TEST_PASSWORD1));
    EXPECT_CALL(*mockUser, getFullName()).WillRepeatedly(testing::Return(TEST_FULLNAME1));

    std::unordered_map<std::string, IUser *> users;
    users[TEST_USERNAME1] = mockUser;

    FileHandler handler(usersFile, postsFile);
    EXPECT_TRUE(handler.saveUsers(users));

    std::ifstream file(usersFile);
    ASSERT_TRUE(file.is_open());

    nlohmann::json json;
    file >> json;

    ASSERT_EQ(json.size(), 1);
    EXPECT_EQ(json[0][USERNAME_LABEL], TEST_USERNAME1);
    EXPECT_EQ(json[0][PASSWORD_LABEL], TEST_PASSWORD1);
    EXPECT_EQ(json[0][FULLNAME_LABEL], TEST_FULLNAME1);

    delete mockUser;
}

TEST_F(FileHandlerTest, GivenMissingPostsFile_WhenLoadingPosts_ThenReturnsFalseAndLeavesMapEmpty)
{
    FileHandler handler(usersFile, postsFile);
    std::map<int, IPost *, std::greater<int>> posts;

    EXPECT_FALSE(handler.loadPosts(posts));
    EXPECT_TRUE(posts.empty());
}

TEST_F(FileHandlerTest, GivenEmptyPostsFile_WhenLoadingPosts_ThenReturnsTrueAndLoadsNothing)
{
    std::ofstream file(postsFile);
    file.close();

    FileHandler handler(usersFile, postsFile);
    std::map<int, IPost *, std::greater<int>> posts;

    EXPECT_TRUE(handler.loadPosts(posts));
    EXPECT_TRUE(posts.empty());
}

TEST_F(FileHandlerTest, GivenSinglePostInFile_WhenLoadingPosts_ThenLoadsPostCorrectly)
{
    nlohmann::json json = nlohmann::json::array({{{POST_ID_LABEL, TEST_POST1_ID},
                                                  {USERNAME_LABEL, TEST_USERNAME1},
                                                  {CONTENT_LABEL, TEST_CONTENT1},
                                                  {TIMESTAMP_LABEL, TEST_TIMESTAMP},
                                                  {LIKERS_LABEL, {TEST_USERNAME2, TEST_USERNAME3}}}});

    std::ofstream file(postsFile);
    file << json;
    file.close();

    FileHandler handler(usersFile, postsFile);
    std::map<int, IPost *, std::greater<int>> posts;

    EXPECT_TRUE(handler.loadPosts(posts));

    ASSERT_EQ(posts.size(), 1);
    IPost *post = posts[TEST_POST1_ID];
    EXPECT_NE(post, nullptr);

    delete post;
}

TEST_F(FileHandlerTest, GivenInvalidJSONInPostsFile_WhenLoadingPosts_ThenThrowsParseError)
{
    std::ofstream file(postsFile);
    file << INVALID_JSON;
    file.close();

    FileHandler handler(usersFile, postsFile);

    std::map<int, IPost *, std::greater<int>> posts;

    EXPECT_THROW(handler.loadPosts(posts), nlohmann::json::parse_error);
}

TEST_F(FileHandlerTest, GivenEmptyPostsMap_WhenSavingPosts_ThenCreatesEmptyJSONArray)
{
    FileHandler handler(usersFile, postsFile);
    std::map<int, IPost *, std::greater<int>> posts;

    EXPECT_TRUE(handler.savePosts(posts));

    std::ifstream file(postsFile);
    ASSERT_TRUE(file.is_open());

    nlohmann::json json;
    file >> json;

    EXPECT_TRUE(json.is_array());
    EXPECT_EQ(json.size(), 0);
}

TEST_F(FileHandlerTest, GivenSinglePost_WhenSavingPosts_ThenWritesCorrectJSON)
{
    FileHandler handler(usersFile, postsFile);
    MockPost *mockPost = new MockPost();

    EXPECT_CALL(*mockPost, getPostId()).WillOnce(testing::Return(TEST_POST1_ID));
    EXPECT_CALL(*mockPost, getUsername()).WillOnce(testing::Return(TEST_USERNAME1));
    EXPECT_CALL(*mockPost, getPostContent()).WillOnce(testing::Return(TEST_CONTENT1));
    EXPECT_CALL(*mockPost, getTimestamp()).WillOnce(testing::Return(TEST_TIMESTAMP));
    EXPECT_CALL(*mockPost, getLikers()).WillOnce(testing::Return(std::unordered_set<std::string>{TEST_USERNAME2, TEST_USERNAME3}));

    std::map<int, IPost *, std::greater<int>> posts;
    posts[10] = mockPost;

    bool result = handler.savePosts(posts);

    EXPECT_TRUE(result);

    std::ifstream file(postsFile);
    nlohmann::json json;
    file >> json;

    EXPECT_EQ(json.size(), 1);
    EXPECT_EQ(json[0][POST_ID_LABEL], TEST_POST1_ID);
    EXPECT_EQ(json[0][USERNAME_LABEL], TEST_USERNAME1);
    EXPECT_EQ(json[0][CONTENT_LABEL], TEST_CONTENT1);
    EXPECT_EQ(json[0][TIMESTAMP_LABEL], TEST_TIMESTAMP);

    std::unordered_set<std::string> expected = {TEST_USERNAME2, TEST_USERNAME3};
    std::unordered_set<std::string> actual;

    for (const auto &value : json[0][LIKERS_LABEL])
        actual.insert(value.get<std::string>());

    EXPECT_EQ(actual, expected);

    delete mockPost;
}
