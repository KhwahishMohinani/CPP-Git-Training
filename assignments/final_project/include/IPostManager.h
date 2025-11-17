#ifndef I_POST_MANAGER_H
#define I_POST_MANAGER_H

#include <string>
#include <map>
#include "IPost.h"
#include "IFileHandler.h"

class IPostManager
{
public:
    virtual IPost *createPost(const std::string &username, const std::string &caption) = 0;
    virtual bool addPost(IPost *post) = 0;
    virtual IPost *getPost(int postId) = 0;
    virtual const std::map<int, IPost *, std::greater<int>> &getAllPosts() const = 0;
    virtual std::map<int, IPost *, std::greater<int>> getUserPosts(const std::string &username) = 0;
    virtual bool addLike(IPost *post, std::string username) = 0;
    virtual bool removeLike(IPost *post, std::string username) = 0;
    virtual bool deletePost(IPost *post) = 0;
    virtual bool removePost(IPost *post) = 0;
    virtual bool removePostsByUser(const std::string &username) = 0;
    virtual void removeLikesByUser(const std::string &username) = 0;
    virtual void deleteAllPosts() = 0;
};

#endif
