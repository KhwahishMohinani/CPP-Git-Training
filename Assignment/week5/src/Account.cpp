#include <iostream>
#include "Account.h"
#include "Transaction.h"

Account::Account(int accountNumber, double balance, const std::string &accountType, int customerId)
    : accountNumber(accountNumber), balance(balance), accountType(accountType), customerId(customerId), transactionsCount(0)
{
    for (int i = 0; i < MAX_TRANSACTIONS; i++)
    {
        transactions[i] = nullptr;
    }
}

long Account::getAccountNumber() const
{
    return accountNumber;
}

double Account::getBalance() const
{
    return balance;
}

std::string Account::getAccountType() const
{
    return accountType;
}

int Account::getCustomerId() const
{
    return customerId;
}

int Account::getTransactionsCount() const
{
    return transactionsCount;
}

bool Account::addBalance(double amount)
{
    bool success = false;
    if (addTransaction("deposit", amount))
    {
        balance += amount;
        success = true;
    }
    return success;
}

bool Account::subtractBalance(double amount)
{
    bool success = false;
    if (addTransaction("withdraw", amount))
    {
        balance -= amount;
        success = true;
    }
    return success;
}

bool Account::addTransaction(const std::string &type, double amount)
{
    bool success = false;
    if (transactionsCount < MAX_TRANSACTIONS)
    {
        transactions[transactionsCount] = new Transaction(transactionsCount + 1, accountNumber, type, amount);
        transactionsCount++;
        success = true;
    }
    return success;
}

Transaction **Account::getTransactions()
{
    return transactions;
}

Account::~Account()
{
    for (int i = 0; i < transactionsCount; i++)
    {
        delete transactions[i];
        transactions[i] = nullptr;
    }
}
