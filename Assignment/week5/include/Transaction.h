#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction
{
private:
    int transactionId;
    long accountNumber;
    std::string type;
    int amount;

public:
    Transaction(int transactionId, long accountNumber, std::string type, int amount);
    int getTransactionId();
    long getAccountNumber();
    std::string getType();
    int getAmount();
};

#endif
