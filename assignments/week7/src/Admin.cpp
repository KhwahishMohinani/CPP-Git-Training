#include <iostream>
#include "Admin.h"
#include "InputHandler.h"
#include "Customer.h"
#include "IAccount.h"
#include "Account.h"
#include "IBank.h"

Admin::Admin(const std::string &name, int userId, const std::string &password, const std::string &type, IBank &bank)
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

int Admin::createAccount(Customer &customer, double balance, const std::string &accountType)
{
    int accountNumber = -1;
    int accountId = bank.getNextAccountId();
    IAccount *account = new Account(accountId, balance, accountType, customer.getUserId());

    if (bank.addAccount(customer, account))
    {
        accountNumber = accountId;
    }
    else
    {
        delete account;
    }
    return accountNumber;
}

void Admin::deleteCustomer(int customerId)
{
    bank.removeCustomerById(customerId);
}

bool Admin::handleRequests()
{
    lastRequestResult = {0, 0, 0};

    AccountRequest **requests = bank.getAllRequests();
    int totalRequests = bank.getRequestCount();

    for (int i = 0; i < totalRequests; i++)
    {
        AccountRequest *request = requests[i];
        if (!request)
        {
            lastRequestResult.failedCount++;
            continue;
        }

        lastRequestResult.processedCount++;

        Customer *customer = bank.getCustomerById(request->customerId);
        if (!customer)
        {
            lastRequestResult.failedCount++;
            continue;
        }

        int accountId = bank.getNextAccountId();
        IAccount *account = new Account(accountId, request->initialBalance, request->accountType, customer->getUserId());
        bool createdAccount = bank.addAccount(*customer, account);
        if (createdAccount)
        {
            lastRequestResult.createdCount++;
        }
        else
        {
            lastRequestResult.failedCount++;
        }
    }

    bank.clearRequests();
    return (lastRequestResult.createdCount > 0);
}

RequestResult Admin::getLastResult() const
{
    return lastRequestResult;
}
