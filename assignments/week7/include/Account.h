#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "IAccount.h"
#include "constants.h"

class Transaction;

class Account : public IAccount
{
private:
    long accountNumber;
    double balance;
    std::string accountType;
    int customerId;
    Transaction *transactions[MAX_TRANSACTIONS];
    int transactionsCount;

public:
    Account(int accountNumber, double balance, const std::string &accountType, int customerId);
    long getAccountNumber() const;
    double getBalance() const;
    int getTransactionsCount() const;
    std::string getAccountType() const;
    int getCustomerId() const;
    bool addBalance(double amount);
    bool subtractBalance(double amount);
    bool addTransaction(const std::string &type, double amount);
    Transaction **getTransactions();
    ~Account();
};

#endif
