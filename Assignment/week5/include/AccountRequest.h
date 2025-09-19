#ifndef ACCOUNT_REQUEST_H
#define ACCOUNT_REQUEST_H

#include <string>

struct AccountRequest
{
    double initialBalance;
    int customerId;
    std::string type;

    AccountRequest(int id, double balance, std::string type);
};

#endif
