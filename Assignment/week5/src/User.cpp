#include <iostream>
#include "../include/User.h"
#include "../include/IBank.h"
#include "../include/Bank.h"
#include "../include/Account.h"
#include "../include/Authentication.h"
#include "../include/InputHandler.h"

User *User::login(IBank &bank)
{
    InputHandler inputHandler;
    int id, value;
    std::string pass, input;
    User *loggedInUser = nullptr;

    while (true)
    {
        std::cout << "Enter user id: ";
        std::cin >> input;
        if (inputHandler.isValidInt(input, value))
        {
            id = value;
            break;
        }
        else
        {
            std::cout << "Please enter the correct id\n";
        }
    }
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
void User::deposit(IAccount *account, double amount)
{
    std::cout << "Not allowed!\n";
}
void User::withdraw(IAccount *account, double amount)
{
    std::cout << "Not allowed!\n";
}

void User::showMenu(IBank &bank)
{
    std::cout << "Generic User has no menu.\n";
}
