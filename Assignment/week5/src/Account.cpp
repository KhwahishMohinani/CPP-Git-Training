#include "../include/Account.h"

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
