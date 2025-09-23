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
    Transaction(int transactionId, long accountNumber, const std::string &type, double amount);
    int getTransactionId() const;
    long getAccountNumber() const;
    std::string getType() const;
    int getAmount() const;
};

#endif
