#ifndef BANK_H
#define BANK_H

#include "IBank.h"
#define MAX_ACCOUNTS 100
#define MAX_USERS 100

class IAccount;
class User;

class Bank : public IBank
{
private:
    IAccount *accounts[MAX_ACCOUNTS];
    User *users[MAX_USERS];
    static int accountsCount;
    static int usersCount;
    static int customersCount;
    static int adminsCount;

public:
    void addAccount(User *loggedIn);
    /*void removeAccount();
    void getAccount();*/
    void addUser(std::string type);
    /*void showAccount();
    void removeUser();*/
    int getUsersCount();
    int getAccountsCount();
    int getCustomercount();
    User **getUsers();
    User *findUserByCredentials(int id, const std::string &password);
};

#endif
