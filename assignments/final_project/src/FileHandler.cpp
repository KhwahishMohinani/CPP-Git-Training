#include "FileHandler.h"
#include "User.h"
#include "Post.h"
#include "constants.h"
#include <fstream>
#include <nlohmann/json.hpp>

FileHandler::FileHandler(const std::string &usersFileName, const std::string &postsFileName)
    : usersFile(usersFileName), postsFile(postsFileName)
{
}

bool FileHandler::loadUsers(std::unordered_map<std::string, IUser *> &users)
{
    bool success = false;
    std::ifstream file(usersFile);
    if (file.is_open())
    {
        if (file.peek() == std::ifstream::traits_type::eof())
        {
            success = true;
        }
        else
        {
            nlohmann::json json;
            file >> json;

            for (const auto &item : json)
            {
                std::string username = item[USERNAME_LABEL];
                std::string password = item[PASSWORD_LABEL];
                std::string fullName = item[FULLNAME_LABEL];
                users[username] = new User(username, password, fullName);
            }
            success = true;
        }
    }
    return success;
}

bool FileHandler::saveUsers(const std::unordered_map<std::string, IUser *> &users)
{
    bool success = false;
    nlohmann::json json = nlohmann::json::array();

    for (const auto &[username, userPtr] : users)
    {
        if (userPtr)
        {
            json.push_back({{USERNAME_LABEL, userPtr->getUsername()},
                            {PASSWORD_LABEL, userPtr->getPassword()},
                            {FULLNAME_LABEL, userPtr->getFullName()}});
        }
    }

    std::ofstream file(usersFile);
    if (file.is_open())
    {
        file << std::setw(4) << json;
        success = true;
    }
    return success;
}

bool FileHandler::loadPosts(std::map<int, IPost *, std::greater<int>> &posts)
{
    bool success = false;
    std::ifstream file(postsFile);
    if (file.is_open())
    {
        if (file.peek() == std::ifstream::traits_type::eof())
        {
            success = true;
        }
        else
        {
            nlohmann::json json;
            file >> json;

            for (const auto &item : json)
            {
                int postId = item[POST_ID_LABEL];
                std::string username = item[USERNAME_LABEL];
                std::string content = item[CONTENT_LABEL];
                std::string timestamp = item[TIMESTAMP_LABEL];
                std::vector<std::string> likers = item[LIKERS_LABEL];

                Post *post = new Post(postId, username, content, timestamp);
                for (const auto &liker : likers)
                    post->addLike(liker);

                posts[postId] = post;
            }
            success = true;
        }
    }

    return success;
}

bool FileHandler::savePosts(const std::map<int, IPost *, std::greater<int>> &posts)
{
    bool success = false;
    nlohmann::json json = nlohmann::json::array();

    for (const auto &[id, post] : posts)
    {
        if (post)
        {
            json.push_back({{POST_ID_LABEL, post->getPostId()},
                            {USERNAME_LABEL, post->getUsername()},
                            {CONTENT_LABEL, post->getPostContent()},
                            {TIMESTAMP_LABEL, post->getTimestamp()},
                            {LIKERS_LABEL, post->getLikers()}});
        }
    }

    std::ofstream file(postsFile);
    if (file.is_open())
    {
        file << std::setw(4) << json;
        success = true;
    }
    return success;
}