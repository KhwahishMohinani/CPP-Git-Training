#ifndef I_FILE_HANDLER_H
#define I_FILE_HANDLER_H

#include <map>
#include <unordered_map>
#include <string>
#include "IUser.h"
#include "IPost.h"

class IFileHandler
{
public:
    virtual ~IFileHandler() {};
    virtual bool loadUsers(std::unordered_map<std::string, IUser *> &users) = 0;
    virtual bool saveUsers(const std::unordered_map<std::string, IUser *> &users) = 0;

    virtual bool loadPosts(std::map<int, IPost *, std::greater<int>> &posts) = 0;
    virtual bool savePosts(const std::map<int, IPost *, std::greater<int>> &posts) = 0;
};

#endif
