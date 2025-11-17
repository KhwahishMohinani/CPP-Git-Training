#include "PostManager.h"
#include "MockFileHandler.h"
#include "MockPost.h"
#include "constants.h"
#include <gtest/gtest.h>

class PostManagerTest : public ::testing::Test
{
protected:
    MockFileHandler fileHandler;
    PostManager *postManager;
    std::map<int, IPost *, std::greater<int>> emptyPosts;

    void SetUp() override
    {
        EXPECT_CALL(fileHandler, loadPosts(testing::_))
            .WillOnce(
                testing::DoAll(
                    testing::SetArgReferee<0>(emptyPosts),
                    testing::Return(true)));

        postManager = new PostManager(&fileHandler);
    }

    void TearDown() override
    {
        delete postManager;
    }
};

TEST_F(PostManagerTest, GivenMissingPostId_WhenGetPostCalled_ThenReturnNullptr)
{
    IPost *result = postManager->getPost(TEST_POST1_ID);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PostManagerTest, GivenExistingPost_WhenGetPostCalled_ThenReturnThatPost)
{
    MockPost *mockPost = new MockPost();

    postManager->addPost(mockPost);

    EXPECT_EQ(postManager->getPost(mockPost->getPostId()), mockPost);

    delete mockPost;
}

TEST_F(PostManagerTest, GivenNewPost_WhenAddPostCalled_ThenStorePostAndSavePosts)
{
    MockPost *mockPost = new MockPost();

    EXPECT_CALL(*mockPost, getPostId())
        .WillRepeatedly(testing::Return(TEST_POST1_ID));

    EXPECT_CALL(fileHandler, savePosts(testing::_))
        .Times(1);

    bool result = postManager->addPost(mockPost);

    EXPECT_TRUE(result);
    EXPECT_EQ(postManager->getPost(TEST_POST1_ID), mockPost);

    delete mockPost;
}

TEST_F(PostManagerTest, GivenNullPost_WhenAddPostCalled_ThenReturnFalse)
{
    EXPECT_FALSE(postManager->addPost(nullptr));
}

TEST_F(PostManagerTest, GivenEmptyUsername_WhenCreatePostCalled_ThenReturnNullptr)
{
    IPost *post = postManager->createPost("", TEST_CONTENT1);
    EXPECT_EQ(post, nullptr);
}

TEST_F(PostManagerTest, GivenEmptyCaption_WhenCreatePostCalled_ThenReturnNullptr)
{
    IPost *post = postManager->createPost(TEST_USERNAME1, "");
    EXPECT_EQ(post, nullptr);
}

TEST_F(PostManagerTest, GivenValidUsernameAndCaption_WhenCreatePostCalled_ThenReturnNewPost)
{
    IPost *post = postManager->createPost(TEST_USERNAME1, TEST_CONTENT1);
    EXPECT_NE(post, nullptr);
}

TEST_F(PostManagerTest, GivenUserWithNoPosts_WhenGetUserPostsCalled_ThenReturnEmptyList)
{
    auto result = postManager->getUserPosts(TEST_USERNAME1);
    EXPECT_TRUE(result.empty());
}

TEST_F(PostManagerTest, GivenMultiplePostsByDifferentUsers_WhenGetUserPostsCalled_ThenReturnOnlyPostsOfThatUser)
{
    MockPost *post1 = new MockPost();
    EXPECT_CALL(*post1, getPostId()).WillRepeatedly(testing::Return(TEST_POST1_ID));
    EXPECT_CALL(*post1, getUsername()).WillRepeatedly(testing::Return(std::string(TEST_USERNAME1)));
    postManager->addPost(post1);

    MockPost *post2 = new MockPost();
    EXPECT_CALL(*post2, getPostId()).WillRepeatedly(testing::Return(TEST_POST2_ID));
    EXPECT_CALL(*post2, getUsername()).WillRepeatedly(testing::Return(std::string(TEST_USERNAME2)));
    postManager->addPost(post2);

    MockPost *post3 = new MockPost();
    EXPECT_CALL(*post3, getPostId()).WillRepeatedly(testing::Return(TEST_POST3_ID));
    EXPECT_CALL(*post3, getUsername()).WillRepeatedly(testing::Return(std::string(TEST_USERNAME1)));
    postManager->addPost(post3);

    auto result = postManager->getUserPosts(TEST_USERNAME1);

    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.at(TEST_POST1_ID), post1);
    EXPECT_EQ(result.at(TEST_POST3_ID), post3);

    delete post1;
    delete post2;
    delete post3;
}

TEST_F(PostManagerTest, GivenMultipleUserPosts_WhenGetUserPostsCalled_ThenReturnPostsInDescendingOrder)
{
    MockPost *post1 = new MockPost();
    MockPost *post2 = new MockPost();
    MockPost *post3 = new MockPost();

    EXPECT_CALL(*post1, getPostId()).WillRepeatedly(testing::Return(TEST_POST1_ID));
    EXPECT_CALL(*post2, getPostId()).WillRepeatedly(testing::Return(TEST_POST2_ID));
    EXPECT_CALL(*post3, getPostId()).WillRepeatedly(testing::Return(TEST_POST3_ID));

    EXPECT_CALL(*post1, getUsername()).WillRepeatedly(testing::Return(std::string(TEST_USERNAME1)));
    EXPECT_CALL(*post2, getUsername()).WillRepeatedly(testing::Return(std::string(TEST_USERNAME1)));
    EXPECT_CALL(*post3, getUsername()).WillRepeatedly(testing::Return(std::string(TEST_USERNAME1)));

    postManager->addPost(post1);
    postManager->addPost(post2);
    postManager->addPost(post3);

    auto result = postManager->getUserPosts(TEST_USERNAME1);

    auto it = result.begin();
    EXPECT_EQ(it->first, TEST_POST3_ID);
    ++it;
    EXPECT_EQ(it->first, TEST_POST2_ID);
    ++it;
    EXPECT_EQ(it->first, TEST_POST1_ID);

    delete post1;
    delete post2;
    delete post3;
}

TEST_F(PostManagerTest, GivenPostNotLikedByUser_WhenAddLikeCalled_ThenAddLikeAndSavePosts)
{
    MockPost *post = new MockPost();

    EXPECT_CALL(*post, getPostId())
        .WillRepeatedly(testing::Return(TEST_POST1_ID));

    EXPECT_CALL(*post, addLike(TEST_USERNAME1))
        .WillOnce(testing::Return(true));

    EXPECT_CALL(fileHandler, savePosts(testing::_))
        .WillRepeatedly(testing::Return(true));

    postManager->addPost(post);

    bool result = postManager->addLike(post, TEST_USERNAME1);

    EXPECT_TRUE(result);

    delete post;
}

TEST_F(PostManagerTest, GivenPostAlreadyLikedByUser_WhenAddLikeCalled_ThenDoNotAddDuplicateLike)
{
    MockPost *post = new MockPost();

    EXPECT_CALL(*post, getPostId())
        .WillRepeatedly(testing::Return(TEST_POST1_ID));

    EXPECT_CALL(*post, addLike(TEST_USERNAME2))
        .WillOnce(testing::Return(false));

    EXPECT_CALL(fileHandler, savePosts(testing::_))
        .Times(testing::AtLeast(1));

    postManager->addPost(post);

    bool result = postManager->addLike(post, TEST_USERNAME2);

    EXPECT_FALSE(result);

    delete post;
}

TEST_F(PostManagerTest, GivenNonExistentPost_WhenAddLikeCalled_ThenReturnFalse)
{
    MockPost *post = nullptr;

    bool result = postManager->addLike(post, TEST_USERNAME1);

    EXPECT_FALSE(result);
}

TEST_F(PostManagerTest, GivenPostLikedByUser_WhenRemoveLikeCalled_ThenRemoveLikeAndSavePosts)
{
    MockPost *post = new MockPost();

    EXPECT_CALL(*post, getPostId())
        .WillRepeatedly(testing::Return(TEST_POST1_ID));

    EXPECT_CALL(*post, getLikers())
        .WillRepeatedly(testing::Return(std::unordered_set<std::string>{TEST_USERNAME1}));

    EXPECT_CALL(*post, removeLike(TEST_USERNAME1))
        .Times(1);

    EXPECT_CALL(fileHandler, savePosts(testing::_))
        .Times(2);

    postManager->addPost(post);

    bool result = postManager->removeLike(post, TEST_USERNAME1);

    EXPECT_TRUE(result);

    delete post;
}

TEST_F(PostManagerTest, GivenPostNotLikedByUser_WhenRemoveLikeCalled_ThenDoNotRemoveLike)
{
    MockPost *post = new MockPost();

    EXPECT_CALL(*post, getPostId())
        .WillRepeatedly(testing::Return(TEST_POST1_ID));

    EXPECT_CALL(*post, getLikers())
        .WillRepeatedly(testing::Return(std::unordered_set<std::string>{}));

    EXPECT_CALL(*post, removeLike(testing::_))
        .Times(0);

    EXPECT_CALL(fileHandler, savePosts(testing::_))
        .Times(1);

    postManager->addPost(post);

    bool result = postManager->removeLike(post, TEST_USERNAME2);

    EXPECT_FALSE(result);

    delete post;
}

TEST_F(PostManagerTest, GivenNonExistentPost_WhenRemoveLikeCalled_ThenReturnFalse)
{
    MockPost *post = new MockPost();
    EXPECT_CALL(fileHandler, savePosts(testing::_))
        .Times(0);

    bool result = postManager->removeLike(post, TEST_USERNAME1);

    EXPECT_FALSE(result);

    delete post;
}

TEST_F(PostManagerTest, GivenMultiplePosts_WhenRemoveLikesByUserCalled_ThenRemoveUserLikeFromAllPosts)
{
    MockPost *post1 = new MockPost();
    MockPost *post2 = new MockPost();

    EXPECT_CALL(*post1, removeLike(TEST_USERNAME1)).Times(1);
    EXPECT_CALL(*post2, removeLike(TEST_USERNAME1)).Times(1);

    EXPECT_CALL(*post1, getPostId()).WillRepeatedly(testing::Return(TEST_POST1_ID));
    EXPECT_CALL(*post2, getPostId()).WillRepeatedly(testing::Return(TEST_POST2_ID));
    EXPECT_CALL(fileHandler, savePosts(testing::_)).Times(3);

    postManager->addPost(post1);
    postManager->addPost(post2);

    postManager->removeLikesByUser(TEST_USERNAME1);

    delete post1;
    delete post2;
}

TEST_F(PostManagerTest, GivenNoPosts_WhenRemovingLikesByUser_ThenSavePostsIsCalledOnce)
{
    EXPECT_CALL(fileHandler, savePosts(testing::_)).Times(1);

    postManager->removeLikesByUser(TEST_USERNAME2);
}

TEST_F(PostManagerTest, GivenUserNotInAnyPostLikers_WhenRemovingLikesByUser_ThenRemoveLikeCalledForAllPosts)
{
    MockPost *post1 = new MockPost();
    MockPost *post2 = new MockPost();

    EXPECT_CALL(*post1, getPostId()).WillRepeatedly(testing::Return(TEST_POST1_ID));
    EXPECT_CALL(*post2, getPostId()).WillRepeatedly(testing::Return(TEST_POST2_ID));

    EXPECT_CALL(*post1, removeLike(TEST_USERNAME1)).Times(1);
    EXPECT_CALL(*post2, removeLike(TEST_USERNAME1)).Times(1);
    EXPECT_CALL(fileHandler, savePosts(testing::_)).Times(3);

    postManager->addPost(post1);
    postManager->addPost(post2);

    postManager->removeLikesByUser(TEST_USERNAME1);

    delete post1;
    delete post2;
}

TEST_F(PostManagerTest, GivenValidPost_WhenDeletingPost_ThenReturnsTrue)
{
    MockPost *post = new MockPost();

    bool result = postManager->deletePost(post);

    EXPECT_TRUE(result);
}

TEST_F(PostManagerTest, GivenNullPost_WhenDeletingPost_ThenReturnsFalse)
{
    IPost *post = nullptr;

    bool result = postManager->deletePost(post);

    EXPECT_FALSE(result);
}

TEST_F(PostManagerTest, GivenValidPost_WhenRemovingPost_ThenPostIsRemovedAndReturnsTrue)
{
    MockPost *post = new MockPost();

    EXPECT_CALL(*post, getPostId())
        .WillRepeatedly(testing::Return(TEST_POST1_ID));

    EXPECT_CALL(fileHandler, savePosts(testing::_))
        .Times(2);

    postManager->addPost(post);

    bool result = postManager->removePost(post);

    EXPECT_TRUE(result);
    EXPECT_EQ(postManager->getPost(TEST_POST1_ID), nullptr);

    delete post;
}

TEST_F(PostManagerTest, GivenNonexistentPost_WhenRemovingPost_ThenReturnsFalse)
{
    MockPost *post = new MockPost();

    EXPECT_CALL(*post, getPostId())
        .WillRepeatedly(testing::Return(TEST_POST1_ID));

    EXPECT_CALL(fileHandler, savePosts(testing::_))
        .Times(0);

    bool result = postManager->removePost(post);

    EXPECT_FALSE(result);

    delete post;
}

TEST_F(PostManagerTest, GivenNullPost_WhenRemovingPost_ThenReturnsFalse)
{
    IPost *post = nullptr;

    EXPECT_CALL(fileHandler, savePosts(testing::_))
        .Times(0);

    bool result = postManager->removePost(post);

    EXPECT_FALSE(result);
}

TEST_F(PostManagerTest, GivenMultiplePosts_WhenRemovingPostsByUser_ThenOnlyUserPostsAreRemoved)
{
    MockPost *post1 = new MockPost();
    MockPost *post2 = new MockPost();
    MockPost *post3 = new MockPost();

    EXPECT_CALL(*post1, getPostId()).WillRepeatedly(testing::Return(TEST_POST1_ID));
    EXPECT_CALL(*post2, getPostId()).WillRepeatedly(testing::Return(TEST_POST2_ID));
    EXPECT_CALL(*post3, getPostId()).WillRepeatedly(testing::Return(TEST_POST3_ID));

    EXPECT_CALL(*post1, getUsername()).WillRepeatedly(testing::Return(TEST_USERNAME1));
    EXPECT_CALL(*post2, getUsername()).WillRepeatedly(testing::Return(TEST_USERNAME2));
    EXPECT_CALL(*post3, getUsername()).WillRepeatedly(testing::Return(TEST_USERNAME1));

    EXPECT_CALL(fileHandler, savePosts(testing::_)).Times(4);

    postManager->addPost(post1);
    postManager->addPost(post2);
    postManager->addPost(post3);

    std::map<int, IPost *, std::greater<int>> testPosts;

    bool result = postManager->removePostsByUser(TEST_USERNAME1);

    EXPECT_TRUE(result);
    EXPECT_EQ(postManager->getPost(TEST_POST1_ID), nullptr);
    EXPECT_EQ(postManager->getPost(TEST_POST3_ID), nullptr);
    EXPECT_NE(postManager->getPost(TEST_POST2_ID), nullptr);

    delete post2;
    delete post1;
    delete post3;
}

TEST_F(PostManagerTest, GivenUserWithNoPosts_WhenRemovingPostsByUser_ThenReturnsFalse)
{
    MockPost *post = new MockPost();

    EXPECT_CALL(*post, getPostId()).WillRepeatedly(testing::Return(TEST_POST1_ID));
    EXPECT_CALL(*post, getUsername()).WillRepeatedly(testing::Return(TEST_USERNAME2));
    EXPECT_CALL(fileHandler, savePosts(testing::_)).Times(1);

    postManager->addPost(post);

    bool result = postManager->removePostsByUser(TEST_USERNAME1);

    EXPECT_FALSE(result);
    EXPECT_NE(postManager->getPost(TEST_POST1_ID), nullptr);

    delete post;
}

TEST_F(PostManagerTest, GivenNoPostsExist_WhenRemovingPostsByUser_ThenReturnsFalse)
{
    EXPECT_CALL(fileHandler, savePosts(testing::_)).Times(0);

    bool result = postManager->removePostsByUser(TEST_USERNAME1);

    EXPECT_FALSE(result);
}

TEST_F(PostManagerTest, GivenMultiplePosts_WhenDeletingAllPosts_ThenAllPostsAreRemoved)
{
    MockPost *post1 = new MockPost();
    MockPost *post2 = new MockPost();
    MockPost *post3 = new MockPost();

    EXPECT_CALL(*post1, getPostId()).WillRepeatedly(testing::Return(TEST_POST1_ID));
    EXPECT_CALL(*post2, getPostId()).WillRepeatedly(testing::Return(TEST_POST2_ID));
    EXPECT_CALL(*post3, getPostId()).WillRepeatedly(testing::Return(TEST_POST3_ID));

    EXPECT_CALL(fileHandler, savePosts(testing::_)).Times(3);

    postManager->addPost(post1);
    postManager->addPost(post2);
    postManager->addPost(post3);

    postManager->deleteAllPosts();

    EXPECT_TRUE(postManager->getAllPosts().empty());

    delete post1;
    delete post2;
    delete post3;
}

TEST_F(PostManagerTest, GivenNoPostsExist_WhenDeletingAllPosts_ThenOperationCompletesSafely)
{
    postManager->deleteAllPosts();
    EXPECT_TRUE(postManager->getAllPosts().empty());
}
