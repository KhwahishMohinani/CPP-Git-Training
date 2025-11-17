#include "PostManager.h"
#include "Post.h"
#include <algorithm>

PostManager::PostManager(IFileHandler *fileHandler)
    : fileHandler(fileHandler)
{
    fileHandler->loadPosts(posts);
    if (!posts.empty())
    {
        nextPostId = posts.begin()->first + 1;
    }
    else
    {
        nextPostId = 1;
    }
}

IPost *PostManager::getPost(int postId)
{
    IPost *post = nullptr;
    if (posts.find(postId) != posts.end())
    {
        post = posts[postId];
    }
    return post;
}

const std::map<int, IPost *, std::greater<int>> &PostManager::getAllPosts() const
{
    return posts;
}

IPost *PostManager::createPost(const std::string &username, const std::string &caption)
{
    IPost *post = nullptr;
    if (!username.empty() && !caption.empty())
    {
        int postId = nextPostId++;
        post = new Post(postId, username, caption);
    }

    return post;
}

bool PostManager::addPost(IPost *post)
{
    bool success = false;
    if (post)
    {
        posts[post->getPostId()] = post;
        fileHandler->savePosts(posts);
        success = true;
    }

    return success;
}

std::map<int, IPost *, std::greater<int>> PostManager::getUserPosts(const std::string &username)
{
    std::map<int, IPost *, std::greater<int>> userPosts;

    for (auto &[id, post] : posts)
    {
        if (post->getUsername() == username)
            userPosts[id] = post;
    }

    return userPosts;
}

bool PostManager::addLike(IPost *post, std::string username)
{
    bool success = false;

    if (post)
    {
        bool inserted = post->addLike(username);
        if (inserted)
        {
            fileHandler->savePosts(posts);
            success = true;
        }
    }
    return success;
}

bool PostManager::removeLike(IPost *post, std::string username)
{
    bool success = false;

    if (post)
    {
        auto likedByUser = std::find(post->getLikers().begin(), post->getLikers().end(), username);

        if (likedByUser != post->getLikers().end())
        {
            post->removeLike(username);
            fileHandler->savePosts(posts);
            success = true;
        }
    }
    return success;
}

void PostManager::removeLikesByUser(const std::string &username)
{
    for (auto &pair : posts)
    {
        IPost *post = pair.second;
        post->removeLike(username);
    }

    fileHandler->savePosts(posts);
}

bool PostManager::deletePost(IPost *post)
{
    bool success = false;

    if (post)
    {
        delete post;
        post = nullptr;
        success = true;
    }

    return success;
}

bool PostManager::removePost(IPost *post)
{
    bool success = false;

    if (post)
    {
        auto iterator = posts.find(post->getPostId());

        if (iterator != posts.end())
        {
            posts.erase(iterator);
            fileHandler->savePosts(posts);
            success = true;
        }
    }

    return success;
}

bool PostManager::removePostsByUser(const std::string &username)
{
    bool success = false;

    for (auto iterator = posts.begin(); iterator != posts.end();)
    {
        IPost *post = iterator->second;
        if (post->getUsername() == username)
        {
            delete post;
            iterator = posts.erase(iterator);
            success = true;
        }
        else
        {
            ++iterator;
        }
    }

    if (success)
    {
        fileHandler->savePosts(posts);
    }

    return success;
}

void PostManager::deleteAllPosts()
{
    for (auto iterator = posts.begin(); iterator != posts.end(); ++iterator)
    {
        delete iterator->second;
    }

    posts.clear();
}
