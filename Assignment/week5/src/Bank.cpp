#include <iostream>
#include "Bank.h"
#include "Customer.h"
#include "Admin.h"
#include "IAccount.h"
#include "Account.h"
#include "AccountRequest.h"
#include "InputHandler.h"

Bank::Bank()
    : bankId(1), bankName("My Bank")
{
    admins[adminsCount++] = new Admin("Red", 1, "admin123", "admin", *this);
    admins[adminsCount++] = new Admin("Blue", 2, "admin234", "admin", *this);
    admins[adminsCount++] = new Admin("Green", 3, "admin345", "admin", *this);
}

int Bank::getAccountsCount()
{
    return accountsCount;
}

int Bank::getCustomersCount()
{
    return customersCount;
}

Customer *Bank::addCustomer(std::string &name, std::string &password)
{
    if (customersCount >= MAX_CUSTOMERS)
        return nullptr;

    int customerId = customersCount + 1;
    customers[customersCount] = new Customer(name, customerId, password, "customer");
    customersCount++;

    return customers[customersCount - 1];
}

Customer *Bank::findCustomerById(int id)
{
    Customer *customer = nullptr;
    for (int i = 0; i < customersCount; i++)
    {
        if (customers[i]->getUserId() == id)
        {
            customer = customers[i];
        }
    }
    return customer;
}

Customer *Bank::findCustomerByCredentials(int id, const std::string &password)
{
    Customer *customer = nullptr;
    for (int i = 0; i < customersCount; i++)
    {
        customer = customers[i];
        if (customer && customer->getUserId() == id && customer->getPassword() == password)
        {
            break;
        }
        else
        {
            customer = nullptr;
        }
    }
    return customer;
}

IAccount *Bank::addAccount(Customer &customer, double balance, const std::string &accountType)
{
    if (accountsCount >= MAX_ACCOUNTS)
        return nullptr;

    int accountId = accountsCount + 1;
    accounts[accountsCount] = new Account(accountId, balance, accountType, customer.getUserId());
    accountsCount++;

    return accounts[accountsCount - 1];
}

void Bank::removeAccount(IAccount *account)
{
    for (int i = 0; i < accountsCount; i++)
    {
        if (accounts[i] == account)
        {
            delete accounts[i];

            for (int j = i; j < accountsCount - 1; j++)
            {
                accounts[j] = accounts[j + 1];
            }
            accounts[accountsCount - 1] = nullptr;
            accountsCount--;
        }
    }
}

void Bank::removeCustomerById(int id)
{
    for (int i = 0; i < customersCount; i++)
    {
        if (customers[i] && customers[i]->getUserId() == id)
        {
            Customer *customer = customers[i];
            int j = 0;
            while (j < accountsCount)
            {
                if (accounts[j] && accounts[j]->getCustomerId() == id)
                {
                    delete accounts[j];

                    for (int k = j; k < accountsCount - 1; k++)
                    {
                        accounts[k] = accounts[k + 1];
                    }
                    accounts[accountsCount - 1] = nullptr;
                    accountsCount--;
                }
                else
                {
                    j++;
                }
            }

            delete customer;

            for (int j = i; j < customersCount - 1; j++)
            {
                customers[j] = customers[j + 1];
            }
            customers[customersCount - 1] = nullptr;
            customersCount--;

            break;
        }
    }
}

IAccount **Bank::getAccountsByCustomerId(int customerId, int &accountCount)
{
    IAccount **customerAccounts = new IAccount *[accountsCount];
    int customerAccountsCount = 0;

    for (int i = 0; i < accountsCount; i++)
    {
        if (accounts[i] && accounts[i]->getCustomerId() == customerId)
        {
            customerAccounts[customerAccountsCount] = accounts[i];
            customerAccountsCount++;
        }
    }

    accountCount = customerAccountsCount;
    return customerAccounts;
}

Customer **Bank::getAllCustomers()
{
    return customers;
}

IAccount **Bank::getAllAccounts()
{
    return accounts;
}

IAccount *Bank::getAccount(long accountNumber, int customerId)
{
    IAccount *account = nullptr;
    for (int i = 0; i < accountsCount; i++)
    {
        if (accounts[i]->getAccountNumber() == accountNumber &&
            accounts[i]->getCustomerId() == customerId)
        {
            account = accounts[i];
            break;
        }
    }
    return account;
}

Admin *Bank::findAdminByCredentials(int id, const std::string &password)
{
    Admin *admin = nullptr;
    for (int i = 0; i < adminsCount; i++)
    {
        admin = admins[i];
        if (admin && admin->getUserId() == id && admin->getPassword() == password)
        {
            break;
        }
        else
        {
            admin = nullptr;
        }
    }
    return admin;
}

bool Bank::deposit(long accountNumber, int customerId, double amount)
{
    bool success = false;
    IAccount *account = getAccount(accountNumber, customerId);
    if (account)
    {
        account->addBalance(amount);
        success = true;
    }
    return success;
}

bool Bank::withdraw(long accountNumber, int customerId, double amount)
{
    bool success = false;
    IAccount *account = getAccount(accountNumber, customerId);
    if (account && account->getBalance() > amount)
    {
        account->subtractBalance(amount);
        success = true;
    }
    return success;
}

double Bank::getAccountBalance(long accountNumber, int customerId)
{
    IAccount *account = getAccount(accountNumber, customerId);
    return account->getBalance();
}

Transaction **Bank::getAccountTransactions(long accountNumber, int customerId)
{
    IAccount *account = getAccount(accountNumber, customerId);

    return account->getTransactions();
}

int Bank::getAccountTransactionsCount(long accountNumber, int customerId)
{
    int accountTransactionsCount = 0;
    IAccount *account = getAccount(accountNumber, customerId);
    accountTransactionsCount = account->getTransactionsCount();
    return accountTransactionsCount;
}

bool Bank::addAccountRequest(int customerId, double balance, std::string type)
{
    bool success = false;
    if (requestsCount < MAX_REQUESTS)
    {
        requests[requestsCount++] = new AccountRequest(customerId, balance, type);
        success = true;
    }
    return success;
}

AccountRequest **Bank::getAllRequests()
{
    return requests;
}

int Bank::getRequestCount()
{
    return requestsCount;
}

void Bank::clearRequests()
{
    for (int i = 0; i < requestsCount; i++)
    {
        delete requests[i];
        requests[i] = nullptr;
    }
    requestsCount = 0;
}