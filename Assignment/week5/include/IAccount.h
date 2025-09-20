#ifndef IACCOUNT_H
#define IACCOUNT_H

#include <string>

class Transaction;

class IAccount
{

public:
    virtual long getAccountNumber() const = 0;
    virtual double getBalance() const = 0;
    virtual std::string getAccountType() const = 0;
    virtual int getCustomerId() const = 0;
    virtual int getTransactionsCount() const = 0;
    virtual void addBalance(double amount) = 0;
    virtual void subtractBalance(double amount) = 0;
    virtual Transaction **getTransactions() = 0;
    virtual ~IAccount() {};
};

#endif
