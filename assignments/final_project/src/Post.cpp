#include "Post.h"
#include <sstream>
#include <iomanip>
#include <chrono>

Post::Post(int id, const std::string &user, const std::string &text)
    : postId(id), username(user), content(text)
{
    timestamp = getCurrentTime();
}

Post::Post(int id, const std::string &user, const std::string &text, const std::string &time)
    : postId(id), username(user), content(text), timestamp(time)
{
}

int Post::getPostId()
{
    return postId;
}

std::string Post::getCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::stringstream stringstream;
    stringstream << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return stringstream.str();
}

std::string Post::getPostContent()
{
    return content;
}

std::string Post::getUsername()
{
    return username;
}

std::string Post::getTimestamp()
{
    return timestamp;
}

bool Post::addLike(const std::string &username)
{
    return likers.insert(username).second;
}

void Post::removeLike(const std::string &username)
{
    likers.erase(username);
}

bool Post::hasLiked(const std::string &username) const
{
    return likers.find(username) != likers.end();
}

int Post::getLikeCount() const
{
    return likers.size();
}

std::unordered_set<std::string> Post::getLikers()
{
    return likers;
}
