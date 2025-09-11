#ifndef IACCOUNT_H
#define IACCOUNT_H

#include <iostream>

class IAccount
{
private:
    long accountNumber;
    double balance;
    std::string accountType;
    int customerId;

public:
    getAccountDetails();
};

#endif