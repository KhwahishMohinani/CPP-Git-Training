#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "IUserManager.h"

class UserManager : public IUserManager
{
private:
    std::unordered_map<std::string, IUser *> users;
    int nextPostId;
    IFileHandler *fileHandler;

    std::string encodePassword(const std::string &password);

public:
    UserManager(IFileHandler *fileHandler);
    IUser *createUser(const std::string &username, const std::string &password, const std::string &fullname);
    bool addUser(IUser *user);
    bool signUp(const std::string &username, const std::string &password, const std::string &fullname);
    int signIn(std::string username, std::string password);
    IUser *getUserAccount(std::string username);
    bool editProfile(IUser *user, const std::string &newPassword = "", const std::string &newFullName = "");
    bool deleteUser(IUser *user);
    bool removeUser(const std::string &username);
    bool deleteAccount(IUser *user);
    void deleteAllUsers();
};

#endif
