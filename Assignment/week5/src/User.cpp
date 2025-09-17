#include <iostream>
#include "User.h"

User::User(std::string name, int userId, std::string password, std::string type)
{
    this->name = name;
    this->userId = userId;
    this->password = password;
    this->type = type;
}

void User::setUserId(int userId)
{
    this->userId = userId;
}

void User::setPassword(std::string password)
{
    this->password = password;
}

void User::setType(std::string type)
{
    this->type = type;
}

void User::setName(std::string name)
{
    this->name = name;
}

std::string User::getType()
{
    return type;
}

std::string User::getPassword()
{
    return password;
}

int User::getUserId()
{
    return userId;
}

std::string User::getName()
{
    return name;
}
