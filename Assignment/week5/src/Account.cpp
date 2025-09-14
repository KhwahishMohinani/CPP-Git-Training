#include <iostream>
#include "../include/Account.h"
#include "../include/Transaction.h"

Account::Account(int accountNumber, std::string accountType, int customerId)
{
    setAccountNumber(accountNumber);
    setBalance(0);
    setAccountType(accountType);
    setCustomerId(customerId);
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

void Account::showMiniStatement()
{
    int start = 0;
    if (transactionsCount > 5)
    {
        start = transactionsCount - 5;
    }
    std::cout << "Mini Statement(Last 5 transactions):\n";
    for (int i = start; i < transactionsCount; i++)
    {
        std::cout << "Transaction Id: " << transactions[i]->getTransactionId();
        std::cout << " | Account Number: " << transactions[i]->getAccountNumber();
        std::cout << " | Transaction type: " << transactions[i]->getType();
        std::cout << " | Amount: " << transactions[i]->getAmount() << "\n";
    }
}

void Account::showBankStatement()
{
    std::cout << "Bank Statement:\n";
    for (int i = 0; i < transactionsCount; i++)
    {
        std::cout << "Transaction Id: " << transactions[i]->getTransactionId();
        std::cout << " | Account Number: " << transactions[i]->getAccountNumber();
        std::cout << " | Transaction type: " << transactions[i]->getType();
        std::cout << " | Amount: " << transactions[i]->getAmount() << "\n";
    }
}
