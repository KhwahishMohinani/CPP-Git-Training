#ifndef BANK_H
#define BANK_H

#include "IBank.h"
#include "IAccount.h"
#define MAX_ACCOUNTS 100
#define MAX_USERS 100

class Bank : public IBank
{
private:
    IAccount *accounts[MAX_ACCOUNTS];
    User *users[MAX_USERS];

public:
    addAccount();
    removeAccount();
    getAccount();
    addUser();
    removeUser();
};

#endif
