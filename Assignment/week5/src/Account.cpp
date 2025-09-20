#include <iostream>
#include "Account.h"
#include "Transaction.h"

Account::Account(int accountNumber, double balance, std::string accountType, int customerId)
    : accountNumber(accountNumber), balance(balance), accountType(accountType), customerId(customerId)
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

void Account::addBalance(double amount)
{
    balance += amount;
    addTransaction("deposit", amount);
}

void Account::subtractBalance(double amount)
{
    balance -= amount;
    addTransaction("withdraw", amount);
}

void Account::addTransaction(std::string type, double amount)
{
    if (transactionsCount < MAX_TRANSACTIONS)
    {
        transactions[transactionsCount] = new Transaction(transactionsCount + 1, accountNumber, type, amount);
        transactionsCount++;
    }
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
