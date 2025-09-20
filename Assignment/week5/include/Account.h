#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "IAccount.h"

#define MAX_TRANSACTIONS 100

class Transaction;

class Account : public IAccount
{
private:
    long accountNumber;
    double balance;
    std::string accountType;
    int customerId;
    Transaction *transactions[MAX_TRANSACTIONS];
    int transactionsCount = 0;

public:
    Account(int accountNumber, double balance, std::string accountType, int customerId);
    long getAccountNumber() const;
    double getBalance() const;
    int getTransactionsCount() const;
    std::string getAccountType() const;
    int getCustomerId() const;
    void addBalance(double amount);
    void subtractBalance(double amount);
    void addTransaction(std::string type, double amount);
    Transaction **getTransactions();
    ~Account();
};

#endif
