#ifndef MOCK_FILE_HANDLER_H
#define MOCK_FILE_HANDLER_H

#include "IFileHandler.h"
#include <gmock/gmock.h>

class MockFileHandler : public IFileHandler
{
public:
    MOCK_METHOD(bool, loadUsers, ((std::unordered_map<std::string, IUser *> & users)));
    MOCK_METHOD(bool, saveUsers, ((const std::unordered_map<std::string, IUser *> &users)));
    MOCK_METHOD(bool, loadPosts, ((std::map<int, IPost *, std::greater<int>> & posts)));
    MOCK_METHOD(bool, savePosts, ((const std::map<int, IPost *, std::greater<int>> &posts)));
};

#endif
