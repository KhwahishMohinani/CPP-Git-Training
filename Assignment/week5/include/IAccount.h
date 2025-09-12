#ifndef IACCOUNT_H
#define IACCOUNT_H

#include <string>

class IAccount
{
protected:
    long accountNumber;
    double balance;
    std::string accountType;
    int customerId;

public:
    virtual void setAccountNumber(long accountNumber) = 0;
    virtual void setBalance(double balance) = 0;
    virtual void setAccountType(std::string accountType) = 0;
    virtual void setCustomerId(int customerId) = 0;
    virtual long getAccountNumber() = 0;
    virtual double getBalance() = 0;
    virtual std::string getAccountType() = 0;
    virtual int getCustomerId() = 0;
};

#endif
