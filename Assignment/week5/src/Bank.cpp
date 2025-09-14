#include <iostream>
#include "../include/Bank.h"
#include "../include/Customer.h"
#include "../include/Admin.h"
#include "../include/IAccount.h"
#include "../include/Account.h"
#include "../include/InputHandler.h"

int Bank::usersCount = 0;
int Bank::accountsCount = 0;
int Bank::customersCount = 0;
int Bank::adminsCount = 0;

int Bank::getUsersCount()
{
    return usersCount;
}

int Bank::getAccountsCount()
{
    return accountsCount;
}

int Bank::getCustomercount()
{
    return customersCount;
}

User **Bank::getUsers()
{
    return users;
}

void Bank::addUser()
{
    InputHandler inputHandler;
    std::string input;
    int type, value;
    while (true)
    {
        std::cout << "Signup as \n1. Customer\n2. Admin\n";
        std::cout << "Enter your choice: ";
        std::cin >> input;

        if (inputHandler.isValidInt(input, value) && (value == 1 || value == 2))
        {
            type = value;
            break;
        }
        else
        {
            std::cout << "Invalid input! Please enter 1 for Customer or 2 for Admin.\n";
        }
    }
    switch (type)
    {
    case 1:
    {
        std::string password, name, email;
        int contact, value;
        std::string input;
        std::cout << "Enter Password: ";
        std::cin >> password;
        std::cout << "Enter Name: ";
        std::cin >> name;
        while (true)
        {
            std::cout << "Enter Contact: ";
            std::cin >> input;
            if (inputHandler.isValidInt(input, value))
            {
                contact = value;
                break;
            }
            else
                std::cout << "Please enter the correct number\n";
        }
        users[usersCount] = new Customer(name, contact, usersCount + 1, password, "customer");
        usersCount++;
        std::cout << "Customer created successfully!\n";
        std::cout << "Your customer id is: " << usersCount << "\n";
        break;
    }
    case 2:
    {
        std::string password;
        std::cout << "Enter Password: ";
        std::cin >> password;
        users[usersCount] = new Admin(usersCount + 1, password, "admin");
        usersCount++;
        std::cout << "Admin created successfully!\n";
        std::cout << "Your admin id is: " << usersCount << "\n";
        break;
    }
    default:
    {
        std::cout << "Incorrect type\n";
    }
    }
}

User *Bank::findUserById(int id)
{
    for (int i = 0; i < usersCount; i++)
    {
        if (users[i]->getUserId() == id)
        {
            return users[i];
        }
    }
    return nullptr;
}

User *Bank::findUserByCredentials(int id, const std::string &password)
{
    User *user = nullptr;
    for (int i = 0; i < usersCount; i++)
    {
        user = users[i];
        if (user && user->getUserId() == id && user->getPassword() == password)
        {
            break;
        }
        else
        {
            user = nullptr;
        }
    }
    return user;
}

void Bank::addAccount(User *loggedInUser)
{
    std::cout << "Enter the account type (current/savings): ";
    std::string accountType;
    std::cin >> accountType;
    accounts[accountsCount] = new Account(accountsCount + 1, accountType, loggedInUser->getUserId());
    accountsCount++;
    std::cout << "Account created successfully!\n";

    std::cout << "Your Account Number is: " << accountsCount << "\n";
}

void Bank::removeAccount(IAccount *account)
{
    for (int i = 0; i < accountsCount; i++)
    {
        if (accounts[i] == account)
        {
            delete accounts[i];

            for (int j = i; j < accountsCount - 1; j++)
            {
                accounts[j] = accounts[j + 1];
            }
            accounts[accountsCount - 1] = nullptr;
            accountsCount--;

            std::cout << "Account removed successfully!\n";
            break;
        }
    }
}

IAccount *Bank::getAccount(long accountNumber, int customerId)
{
    IAccount *account = nullptr;
    for (int i = 0; i < accountsCount; i++)
    {
        if (accounts[i]->getAccountNumber() == accountNumber &&
            accounts[i]->getCustomerId() == customerId)
        {
            account = accounts[i];
            break;
        }
    }
    return account;
}

IAccount *Bank::getAccountByAccountNumber(long accountNumber)
{
    for (int i = 0; i < accountsCount; i++)
    {
        if (accounts[i]->getAccountNumber() == accountNumber)
        {
            return accounts[i];
        }
    }
    return nullptr;
}

void Bank::removeUser()
{
    InputHandler inputHandler;
    std::cout << "Enter User ID to remove: ";
    int id, value;
    std::string input;
    while (true)
    {
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
    bool found = false;
    for (int i = 0; i < usersCount; i++)
    {
        if (users[i] && users[i]->getUserId() == id)
        {
            delete users[i];
            for (int j = i; j < usersCount - 1; j++)
            {
                users[j] = users[j + 1];
            }
            users[usersCount - 1] = nullptr;
            usersCount--;
            std::cout << "User removed successfully!\n";
            found = true;
            break;
        }
    }
    if (!found)
    {
        std::cout << "User not found!\n";
    }
}

void Bank::showAllAccounts()
{
    if (accountsCount == 0)
    {
        std::cout << "No accounts available!\n";
        return;
    }
    for (int i = 0; i < accountsCount; i++)
    {
        std::cout << "Account " << accounts[i]->getAccountNumber();
        std::cout << " | Type: " << accounts[i]->getAccountType();
        std::cout << " | Balance: " << accounts[i]->getBalance() << "\n";
    }
}
