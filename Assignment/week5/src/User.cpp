#include <iostream>
#include "../include/User.h"
#include "../include/IBank.h"
#include "../include/Bank.h"
#include "../include/Authentication.h"

User *User::login(IBank &bank)
{
    int id;
    std::string pass;
    int index = -1;
    User *loggedInUser = nullptr;

    std::cout << "Enter user id: ";
    std::cin >> id;
    std::cout << "Enter password: ";
    std::cin >> pass;
    Authentication authentication;
    loggedInUser = authentication.login(bank, id, pass);
    return loggedInUser;
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
