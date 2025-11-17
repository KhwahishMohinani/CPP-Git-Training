#ifndef POST_H
#define POST_H

#include "IPost.h"

class Post : public IPost
{
private:
    int postId;
    std::string username;
    std::string content;
    std::string timestamp;
    std::unordered_set<std::string> likers;

    std::string getCurrentTime();

public:
    Post(int id, const std::string &user, const std::string &text);
    Post(int id, const std::string &user, const std::string &text, const std::string &time);
    int getPostId();
    std::string getPostContent();
    std::string getTimestamp();
    std::string getUsername();
    bool addLike(const std::string &username);
    void removeLike(const std::string &username);
    bool hasLiked(const std::string &username) const;
    int getLikeCount() const;
    std::unordered_set<std::string> getLikers();
};

#endif
