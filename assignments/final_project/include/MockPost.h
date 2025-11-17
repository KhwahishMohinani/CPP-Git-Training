#ifndef MOCK_POST_H
#define MOCK_POST_H

#include "IPost.h"
#include <gmock/gmock.h>

class MockPost : public IPost
{
public:
    MOCK_METHOD(int, getPostId, ());
    MOCK_METHOD(std::string, getPostContent, ());
    MOCK_METHOD(std::string, getTimestamp, ());
    MOCK_METHOD(std::string, getUsername, ());
    MOCK_METHOD(bool, addLike, (const std::string &username));
    MOCK_METHOD(void, removeLike, (const std::string &username));
    MOCK_METHOD(bool, hasLiked, (const std::string &username), (const));
    MOCK_METHOD(int, getLikeCount, (), (const));
    MOCK_METHOD(std::unordered_set<std::string>, getLikers, ());
};

#endif
