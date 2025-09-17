#include <iostream>
#include "Account.h"
#include "Transaction.h"

Account::Account(int accountNumber, std::string accountType, int customerId)
{
    this->accountNumber = accountNumber;
    this->balance = 0;
    this->accountType = accountType;
    this->customerId = customerId;
    for (int i = 0; i < MAX_TRANSACTIONS; i++)
    {
        transactions[i] = nullptr;
    }
}

long Account::getAccountNumber()
{
    return accountNumber;
}
double Account::getBalance()
{
    return balance;
}
std::string Account::getAccountType()
{
    return accountType;
}
int Account::getCustomerId()
{
    return customerId;
}

int Account::getTransactionsCount()
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
