#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "IAccount.h"
#define MAX_TRANSACTIONS 100
class Account : public IAccount
{
private:
    Transaction *transactions[MAX_TRANSACTIONS];

public:
    addBalance();
    subtractBalance();
    getTransaction();
};

#endif
