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
    void addAccount(User *loggedIn) override;
    void removeAccount(IAccount *account) override;
    void addUser(std::string type) override;
    int getUsersCount();
    int getAccountsCount();
    int getCustomercount();
    User **getUsers();
    User *findUserByCredentials(int id, const std::string &password) override;
    IAccount *getAccount(long accountNumber, int customerId) override;
    IAccount *getAccountByAccountNumber(long accountNumber) override;
    void removeUser() override;
    void showAllAccounts() override;
};

#endif
