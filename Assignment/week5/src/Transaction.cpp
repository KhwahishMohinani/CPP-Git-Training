#include "../include/Transaction.h"

Transaction::Transaction(int transactionId, long accountNumber, std::string type, int amount)
{
    this->transactionId = transactionId;
    this->accountNumber = accountNumber;
    this->type = type;
    this->amount = amount;
}

long Transaction::getAccountNumber()
{
    return accountNumber;
}

int Transaction::getTransactionId()
{
    return transactionId;
}

std::string Transaction::getType()
{
    return type;
}

int Transaction::getAmount()
{
    return amount;
}
