#include "Post.h"
#include "constants.h"
#include <gtest/gtest.h>

class PostTest : public ::testing::Test
{
protected:
    Post *post1;
    Post *post2;

    void SetUp() override
    {
        post1 = new Post(1, TEST_USERNAME1, TEST_CONTENT1);
        post2 = new Post(1, TEST_USERNAME1, TEST_CONTENT1, TEST_TIMESTAMP);
    }

    void TearDown() override
    {
        delete post1;
        delete post2;
    }
};

TEST_F(PostTest, GivenPostWithoutTimestamp_WhenConstructed_ThenGettersReturnCorrectValuesAndTimestampIsSet)
{

    EXPECT_EQ(post1->getPostId(), 1);
    EXPECT_EQ(post1->getUsername(), TEST_USERNAME1);
    EXPECT_EQ(post1->getPostContent(), TEST_CONTENT1);

    EXPECT_FALSE(post1->getTimestamp().empty());
}

TEST_F(PostTest, GivenPostWithTimestamp_WhenConstructed_ThenGettersReturnCorrectValues)
{
    EXPECT_EQ(post2->getPostId(), 1);
    EXPECT_EQ(post2->getUsername(), TEST_USERNAME1);
    EXPECT_EQ(post2->getPostContent(), TEST_CONTENT1);
    EXPECT_EQ(post2->getTimestamp(), TEST_TIMESTAMP);
}

TEST_F(PostTest, GivenPostWithoutLikes_WhenAddingSingleLike_ThenUserIsAddedAndLikeCountIsUpdated)
{

    post1->addLike(TEST_USERNAME2);

    EXPECT_TRUE(post1->hasLiked(TEST_USERNAME2));
    EXPECT_EQ(post1->getLikeCount(), 1);
}

TEST_F(PostTest, GivenUserHasAlreadyLikedPost_WhenAddingLikeAgain_ThenLikeIsNotDuplicated)
{
    post1->addLike(TEST_USERNAME2);
    post1->addLike(TEST_USERNAME2);

    EXPECT_TRUE(post1->hasLiked(TEST_USERNAME2));
    EXPECT_EQ(post1->getLikeCount(), 1);
}

TEST_F(PostTest, GivenPostWithMultipleLikes_WhenRemovingExistingLike_ThenLikeIsRemovedAndOthersRemain)
{
    post1->addLike(TEST_USERNAME2);
    post1->addLike(TEST_USERNAME3);

    post1->removeLike(TEST_USERNAME2);

    EXPECT_FALSE(post1->hasLiked(TEST_USERNAME2));
    EXPECT_TRUE(post1->hasLiked(TEST_USERNAME3));
    EXPECT_EQ(post1->getLikeCount(), 1);
}

TEST_F(PostTest, GivenPostWithLikes_WhenRemovingNonExistingLike_ThenExistingLikesRemainUnchanged)
{
    post1->addLike(TEST_USERNAME2);

    post1->removeLike(TEST_USERNAME3);

    EXPECT_TRUE(post1->hasLiked(TEST_USERNAME2));
    EXPECT_EQ(post1->getLikeCount(), 1);
}

TEST_F(PostTest, GivenPostWithNoLikes_WhenRemovingLike_ThenLikeCountRemainsZero)
{
    EXPECT_EQ(post1->getLikeCount(), 0);

    post1->removeLike(TEST_USERNAME2);

    EXPECT_EQ(post1->getLikeCount(), 0);
}

TEST_F(PostTest, GivenUserHasLikedPost_WhenCheckingHasLiked_ThenReturnsTrue)
{
    post1->addLike(TEST_USERNAME2);
    EXPECT_TRUE(post1->hasLiked(TEST_USERNAME2));
}

TEST_F(PostTest, GivenUserHasNotLikedPost_WhenCheckingHasLiked_ThenReturnsFalse)
{
    post1->addLike(TEST_USERNAME2);
    EXPECT_FALSE(post1->hasLiked(TEST_USERNAME3));
}

TEST_F(PostTest, GivenUserHasLikedPost_WhenRemovingLike_ThenHasLikedReturnsFalse)
{
    post1->addLike(TEST_USERNAME2);
    post1->removeLike(TEST_USERNAME2);

    EXPECT_FALSE(post1->hasLiked(TEST_USERNAME2));
}

TEST_F(PostTest, GivenMultipleUsersHaveLikedPost_WhenGettingLikers_ThenReturnsAllUsers)
{
    post1->addLike(TEST_USERNAME2);
    post1->addLike(TEST_USERNAME3);
    post1->addLike(TEST_USERNAME1);

    auto likers = post1->getLikers();

    EXPECT_EQ(likers.size(), 3);
    EXPECT_TRUE(likers.find(TEST_USERNAME3) != likers.end());
    EXPECT_TRUE(likers.find(TEST_USERNAME2) != likers.end());
    EXPECT_TRUE(likers.find(TEST_USERNAME1) != likers.end());
}

TEST_F(PostTest, GivenNoLikes_WhenGettingLikers_ThenReturnEmptyList)
{
    auto likers = post1->getLikers();

    EXPECT_TRUE(likers.empty());
}
