#ifndef ACCOUNT_REQUEST_H
#define ACCOUNT_REQUEST_H

#include <string>

struct AccountRequest
{
    double initialBalance;
    int customerId;
    std::string accountType;

    AccountRequest(int id, double balance, std::string type)
        : customerId(id), initialBalance(balance), accountType(type)
    {
    }
};

#endif
