#include "Transaction.h"

Transaction::Transaction(int transactionId, long accountNumber, std::string type, double amount)
    : transactionId(transactionId), accountNumber(accountNumber), type(type), amount(amount)
{
}

long Transaction::getAccountNumber() const
{
    return accountNumber;
}

int Transaction::getTransactionId() const
{
    return transactionId;
}

std::string Transaction::getType() const
{
    return type;
}

int Transaction::getAmount() const
{
    return amount;
}
