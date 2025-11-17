#ifndef MOCK_USER_H
#define MOCK_USER_H

#include "IUser.h"
#include "gmock/gmock.h"

class MockUser : public IUser
{
public:
    MOCK_METHOD(std::string, getUsername, ());
    MOCK_METHOD(std::string, getPassword, ());
    MOCK_METHOD(std::string, getFullName, ());
    MOCK_METHOD(void, setFullName, (const std::string &name));
    MOCK_METHOD(void, setPassword, (const std::string &password));
};

#endif
