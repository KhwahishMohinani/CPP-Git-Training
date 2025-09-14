#include <iostream>
#include "../include/Bank.h"
#include "../include/Customer.h"
#include "../include/Admin.h"
#include "../include/IAccount.h"
#include "../include/Account.h"

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

void Bank::addUser(std::string type)
{
    if (type == "customer")
    {
        std::string password, name, email;
        int contact;
        std::cout << "Enter Password: ";
        std::cin >> password;
        std::cout << "Enter Name: ";
        std::cin >> name;
        std::cout << "Enter Contact: ";
        std::cin >> contact;
        std::cout << "Enter Email: ";
        std::cin >> email;
        users[usersCount] = new Customer(name, email, contact, usersCount, password, type);
        std::cout << "Customer created successfully!\n";
        std::cout << "Your customer id is: " << usersCount << "\n";
        usersCount++;
    }
    else if (type == "admin")
    {
        std::string password;
        std::cout << "Enter Password: ";
        std::cin >> password;
        users[usersCount] = new Admin(usersCount, password, type);
        std::cout << "Admin created successfully!\n";
        std::cout << "Your admin id is: " << usersCount << "\n";
        usersCount++;
    }
    else
    {
        std::cout << "Incorrect type\n";
    }
}

User *Bank::findUserByCredentials(int id, const std::string &password)
{
    for (int i = 0; i < usersCount; i++)
    {
        User *user = users[i];
        if (user && user->getUserId() == id && user->getPassword() == password)
        {
            return user;
        }
    }
    return nullptr;
}

void Bank::addAccount(User *loggedIn)
{
    std::cout << "Enter the account type: ";
    std::string accountType;
    std::cin >> accountType;
    accounts[accountsCount] = new Account(accountsCount + 1, accountType, loggedIn->getUserId());
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
    for (int i = 0; i < accountsCount; i++)
    {
        if (accounts[i]->getAccountNumber() == accountNumber &&
            accounts[i]->getCustomerId() == customerId)
        {
            return accounts[i];
        }
    }
    return nullptr;
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
    std::cout << "Enter User ID to remove: ";
    int id;
    std::cin >> id;

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
        std::cout << "Account " << accounts[i]->getAccountNumber()
                  << " | Type: " << accounts[i]->getAccountType()
                  << " | Balance: " << accounts[i]->getBalance() << "\n";
    }
}
