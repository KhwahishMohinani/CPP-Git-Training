#include "Transaction.h"

Transaction::Transaction(int transactionId, long accountNumber, std::string type, int amount)
    : transactionId(transactionId), accountNumber(accountNumber), type(type), amount(amount)
{
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
