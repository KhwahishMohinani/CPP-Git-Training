#ifndef POST_MANAGER_H
#define POST_MANAGER_H

#include "IPostManager.h"

class PostManager : public IPostManager
{
private:
    std::map<int, IPost *, std::greater<int>> posts;
    int nextPostId;
    IFileHandler *fileHandler;

public:
    PostManager(IFileHandler *fileHandler);
    IPost *createPost(const std::string &username, const std::string &caption);
    bool addPost(IPost *post);
    IPost *getPost(int postId);
    const std::map<int, IPost *, std::greater<int>> &getAllPosts() const;
    std::map<int, IPost *, std::greater<int>> getUserPosts(const std::string &username);
    bool addLike(IPost *post, std::string username);
    bool removeLike(IPost *post, std::string username);
    bool deletePost(IPost *post);
    bool removePost(IPost *post);
    bool removePostsByUser(const std::string &username);
    void removeLikesByUser(const std::string &username);
    void deleteAllPosts();
};

#endif
