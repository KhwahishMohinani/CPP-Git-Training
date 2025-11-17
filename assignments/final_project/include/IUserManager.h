#ifndef I_USER_MANAGER_H
#define I_USER_MANAGER_H

#include <string>
#include <unordered_map>
#include "IUser.h"
#include "IFileHandler.h"

class IUserManager
{
public:
    virtual IUser *createUser(const std::string &username, const std::string &password, const std::string &fullname) = 0;
    virtual bool addUser(IUser *user) = 0;
    virtual bool signUp(const std::string &username, const std::string &password, const std::string &fullname) = 0;
    virtual int signIn(std::string username, std::string password) = 0;
    virtual IUser *getUserAccount(std::string username) = 0;
    virtual bool editProfile(IUser *user, const std::string &newPassword = "", const std::string &newFullName = "") = 0;
    virtual bool deleteUser(IUser *user) = 0;
    virtual bool removeUser(const std::string &username) = 0;
    virtual bool deleteAccount(IUser *user) = 0;
    virtual void deleteAllUsers() = 0;
};

#endif
