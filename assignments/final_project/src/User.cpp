#include "User.h"
#include "Post.h"

User::User(const std::string &username, const std::string &password, const std::string &fullName)
    : username(username), password(password), fullName(fullName)
{
}

std::string User::getUsername()
{
    return username;
}

std::string User::getPassword()
{
    return password;
}

std::string User::getFullName()
{
    return fullName;
}

void User::setFullName(const std::string &name)
{
    fullName = name;
}

void User::setPassword(const std::string &password)
{
    this->password = password;
}
