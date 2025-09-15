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
    int accountsCount = 0;
    int usersCount = 0;
    int customersCount = 0;
    int adminsCount = 0;

public:
    int getUsersCount();
    int getAccountsCount();
    int getCustomercount();
    void addAccount(User loggedInUser);
    void removeAccount(IAccount *account);
    void addUser();
    User **getUsers();
    User *findUserById(int id);
    User *findUserByCredentials(int id, const std::string &password);
    IAccount *getAccount(long accountNumber, int customerId);
    IAccount *getAccountByAccountNumber(long accountNumber);
    void removeUser();
    void showAllAccounts();
};

#endif
