#include "UserManager.h"
#include "User.h"
#include "constants.h"

UserManager::UserManager(IFileHandler *fileHandler)
    : fileHandler(fileHandler)
{
    fileHandler->loadUsers(users);
}

IUser *UserManager::createUser(const std::string &username, const std::string &password, const std::string &fullname)
{
    IUser *user = nullptr;
    if (!username.empty() && !password.empty() && !fullname.empty())
    {
        user = new User(username, password, fullname);
    }
    return user;
}

bool UserManager::addUser(IUser *user)
{
    bool success = false;
    if (user)
    {
        const std::string &username = user->getUsername();

        if (users.find(username) == users.end())
        {
            users[username] = user;
            fileHandler->saveUsers(users);
            success = true;
        }
    }

    return success;
}

bool UserManager::signUp(const std::string &username, const std::string &password, const std::string &fullname)
{
    bool success = false;
    if (users.find(username) == users.end())
    {
        IUser *newUser = createUser(username, encodePassword(password), fullname);
        if (addUser(newUser))
        {
            success = true;
        }
    }
    return success;
}

int UserManager::signIn(std::string username, std::string password)
{
    int errorCode = SIGN_IN_SUCCESS;

    if (users.find(username) == users.end())
    {
        errorCode = INVALID_USERNAME;
    }
    else
    {
        if (encodePassword(password) != users[username]->getPassword())
        {
            errorCode = INVALID_PASSWORD;
        }
    }
    return errorCode;
}

IUser *UserManager::getUserAccount(std::string username)
{
    IUser *user = nullptr;
    auto iterator = users.find(username);
    if (iterator != users.end())
    {
        user = iterator->second;
    }
    return user;
}

bool UserManager::editProfile(IUser *user, const std::string &newPassword, const std::string &newFullName)
{
    bool success = false;
    if (user)
    {
        if (!newPassword.empty())
        {
            user->setPassword(encodePassword(newPassword));
        }

        if (!newFullName.empty())
        {
            user->setFullName(newFullName);
        }

        fileHandler->saveUsers(users);
        success = true;
    }
    return success;
}

bool UserManager::deleteUser(IUser *user)
{
    bool success = false;
    if (user)
    {
        delete user;
        user = nullptr;
        success = true;
    }
    return success;
}

bool UserManager::removeUser(const std::string &username)
{
    bool success = false;
    auto iterator = users.find(username);
    if (iterator != users.end())
    {
        users.erase(iterator);
        fileHandler->saveUsers(users);
        success = true;
    }
    return success;
}

bool UserManager::deleteAccount(IUser *user)
{
    bool success = false;
    bool removed = false;
    bool deleted = false;

    if (user)
    {
        removed = removeUser(user->getUsername());
        deleted = deleteUser(user);
    }

    success = deleted && removed;
    if (success)
    {
        fileHandler->saveUsers(users);
    }
    return success;
}

void UserManager::deleteAllUsers()
{
    for (auto iterator = users.begin(); iterator != users.end(); ++iterator)
    {
        delete iterator->second;
    }

    users.clear();
}

std::string UserManager::encodePassword(const std::string &password)
{
    std::string encodedPassword = password;
    for (size_t i = 0; i < encodedPassword.length(); ++i)
    {
        encodedPassword[i] = encodedPassword[i] + 3;
    }
    return encodedPassword;
}
