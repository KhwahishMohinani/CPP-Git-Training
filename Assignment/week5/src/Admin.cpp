#include <iostream>
#include "Admin.h"
#include "InputHandler.h"
#include "Customer.h"
#include "IAccount.h"
#include "structs.h"
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
    return bank.getCustomerById(id);
}

bool Admin::deleteAccount(long accountNumber, int customerId)
{
    return (bank.removeAccount(accountNumber, customerId));
}

int Admin::createAccount(Customer &customer, double balance, std::string &accountType)
{
    IAccount *account = bank.addAccount(customer, balance, accountType);
    return account ? account->getAccountNumber() : -1;
}

void Admin::deleteCustomer(int customerId)
{
    bank.removeCustomerById(customerId);
}

int Admin::handleRequests()
{
    int createdCount = 0;

    AccountRequest **requests = bank.getAllRequests();
    for (int i = 0; i < bank.getRequestCount(); i++)
    {
        AccountRequest *request = requests[i];
        int customerId = request->customerId;
        double balance = request->initialBalance;
        std::string accountType = request->accountType;

        Customer *customer = bank.getCustomerById(customerId);
        if (customer)
        {
            IAccount *account = bank.addAccount(*customer, balance, accountType);
            if (account)
                createdCount++;
        }
    }

    bank.clearRequests();
    return createdCount;
}
