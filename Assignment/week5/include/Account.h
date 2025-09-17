#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "IAccount.h"

#define MAX_TRANSACTIONS 100

class Transaction;

class Account : public IAccount
{
private:
    Transaction *transactions[MAX_TRANSACTIONS];
    int transactionsCount = 0;

public:
    Account(int accountNumber, std::string accountType, int customerId);
    long getAccountNumber();
    double getBalance();
    int getTransactionsCount();
    std::string getAccountType();
    int getCustomerId();
    void addBalance(double amount);
    void subtractBalance(double amount);
    void addTransaction(std::string type, double amount);
    Transaction **getTransactions();
};

#endif
