#include <iostream>
#include "Admin.h"
#include "InputHandler.h"
#include "Customer.h"
#include "IAccount.h"
#include "AccountRequest.h"
#include "IBank.h"

Admin::Admin(std::string name, int userId, std::string password, std::string type, IBank &bank)
    : User(name, userId, password, type), bank(bank)
{
}

Customer **Admin::fetchAllCustomers()
{
    return bank.getAllCustomers();
}

int Admin::fetchCustomersCount()
{
    return bank.getCustomersCount();
}

IAccount **Admin::fetchAllAccounts()
{
    return bank.getAllAccounts();
}

int Admin::fetchAccountsCount()
{
    return bank.getAccountsCount();
}

Customer *Admin::searchCustomerById(int id)
{
    return bank.findCustomerById(id);
}

IAccount *Admin::fetchAccount(int accountNumber, int customerId)
{
    return bank.getAccount(accountNumber, customerId);
}

void Admin::deleteAccount(IAccount *account)
{
    bank.removeAccount(account);
}

IAccount *Admin::createAccount(Customer &customer, double balance, std::string accountType)
{
    return bank.addAccount(customer, balance, accountType);
}

void Admin::handleRequests()
{
    AccountRequest **requests = bank.getAllRequests();
    for (int i = 0; i < bank.getRequestCount(); i++)
    {
        AccountRequest *request = requests[i];
        int customerId = request->customerId;
        double balance = request->initialBalance;
        std::string type = request->type;

        Customer *customer = bank.findCustomerById(customerId);
        if (customer)
        {
            IAccount *account = bank.addAccount(*customer, balance, type);
        }
    }

    bank.clearRequests();
}
