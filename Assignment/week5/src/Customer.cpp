#include <iostream>
#include "Customer.h"
#include "IAccount.h"
#include "IBank.h"
#include "InputHandler.h"

Customer::Customer(std::string name, int contact, int userId, std::string password, std::string type)
{
    this->name = name;
    this->contact = contact;
    setUserId(userId);
    setPassword(password);
    setType(type);
}

void Customer::deposit(IAccount *account, double amount)
{
    if (account && account->getCustomerId() == this->getUserId())
    {
        account->addBalance(amount);
        std::cout << "Deposited " << amount << " successfully. New balance: " << account->getBalance() << "\n";
    }
    else
    {
        std::cout << "You don't own this account\n";
    }
}

void Customer::withdraw(IAccount *account, double amount)
{
    if (account && account->getCustomerId() == this->getUserId())
    {
        if (amount > account->getBalance())
        {
            std::cout << "Insufficient balance\n";
        }
        else
        {
            account->subtractBalance(amount);
            std::cout << "Withdrawn " << amount << " successfully. New balance: " << account->getBalance() << "\n";
        }
    }
    else
    {
        std::cout << "You don't own this account\n";
    }
}

void Customer::showMiniStatement(IAccount *account)
{
    int start = 0;
    int transactionsCount = account->getTransactionsCount();
    if (transactionsCount > 5)
    {
        start = transactionsCount - 5;
    }
    std::cout << "Mini Statement(Last 5 transactions):\n";
    account->getTransactions(start);
}

void Customer::showBankStatement(IAccount *account)
{
    std::cout << "Bank Statement:\n";
    account->getTransactions(0);
}
