#ifndef I_POST_H
#define I_POST_H

#include "unordered_set"
#include <string>

class IPost
{
public:
    virtual int getPostId() = 0;
    virtual std::string getPostContent() = 0;
    virtual std::string getTimestamp() = 0;
    virtual std::string getUsername() = 0;
    virtual bool addLike(const std::string &username) = 0;
    virtual void removeLike(const std::string &username) = 0;
    virtual bool hasLiked(const std::string &username) const = 0;
    virtual int getLikeCount() const = 0;
    virtual std::unordered_set<std::string> getLikers() = 0;
};

#endif
