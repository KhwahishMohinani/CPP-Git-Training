#include <iostream>
#include "User.h"

User::User(std::string name, int userId, std::string password, std::string userType)
    : name(name), userId(userId), password(password), userType(userType)
{
}

std::string User::getUserType() const
{
    return userType;
}

std::string User::getPassword() const
{
    return password;
}

int User::getUserId() const
{
    return userId;
}

std::string User::getName() const
{
    return name;
}
