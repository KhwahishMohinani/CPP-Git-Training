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
    void setAccountNumber(long accountNumber);
    void setBalance(double balance);
    void setAccountType(std::string accountType);
    void setCustomerId(int customerId);
    long getAccountNumber();
    double getBalance();
    std::string getAccountType();
    int getCustomerId();
    void addBalance(double amount);
    void subtractBalance(double amount);
    void addTransaction(std::string type, double amount);
    void showBankStatement();
    void showMiniStatement();
};

#endif
