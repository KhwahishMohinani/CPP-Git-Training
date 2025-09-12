#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "IAccount.h"

#define MAX_TRANSACTIONS 100

class Transaction;

class Account : public IAccount
{
private:
    Transaction *transactions[MAX_TRANSACTIONS];

public:
    Account(int accountNumber, std::string accountType, int customerId);
    /*getAccountDetails();
    addBalance();
    subtractBalance();
    getTransaction();*/
    void setAccountNumber(long accountNumber);
    void setBalance(double balance);
    void setAccountType(std::string accountType);
    void setCustomerId(int customerId);
    long getAccountNumber();
    double getBalance();
    std::string getAccountType();
    int getCustomerId();
};

#endif
