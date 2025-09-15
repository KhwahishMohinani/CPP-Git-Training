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

void Account::setAccountNumber(long accountNumber)
{
    this->accountNumber = accountNumber;
}
void Account::setBalance(double balance)
{
    this->balance = balance;
}
void Account::setAccountType(std::string accountType)
{
    this->accountType = accountType;
}
void Account::setCustomerId(int customerId)
{
    this->customerId = customerId;
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

int Account::getTransactionsCount()
{
    return transactionsCount;
}

void Account::getTransactions(int start)
{
    for (int i = start; i < transactionsCount; i++)
    {
        std::cout << "Transaction Id: " << transactions[i]->getTransactionId();
        std::cout << " | Account Number: " << transactions[i]->getAccountNumber();
        std::cout << " | Transaction type: " << transactions[i]->getType();
        std::cout << " | Amount: " << transactions[i]->getAmount() << "\n";
    }
}
