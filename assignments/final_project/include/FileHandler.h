#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "IFileHandler.h"

class FileHandler : public IFileHandler
{
private:
    std::string usersFile;
    std::string postsFile;

public:
    FileHandler(const std::string &usersFile, const std::string &postsFile);

    bool loadUsers(std::unordered_map<std::string, IUser *> &users);
    bool saveUsers(const std::unordered_map<std::string, IUser *> &users);

    bool loadPosts(std::map<int, IPost *, std::greater<int>> &posts);
    bool savePosts(const std::map<int, IPost *, std::greater<int>> &posts);
};

#endif
