#include <iostream>
#include "Bank.h"
#include "Customer.h"
#include "Admin.h"
#include "IAccount.h"
#include "Account.h"
#include "structs.h"
#include "InputHandler.h"
#include "constants.h"

Bank::Bank(int bankId, const std::string &bankName, const std::string &adminName, const std::string &adminPassword)
    : bankId(bankId),
      bankName(bankName),
      adminsCount(0),
      accountsCount(0),
      nextAdminId(1),
      customersCount(0),
      nextCustomerId(1),
      requestsCount(0),
      nextAccountId(1)
{
    for (int i = 0; i < DEFAULT_ADMIN_COUNT; i++)
    {
        admins[adminsCount++] = new Admin(DEFAULT_ADMINS[i].name, nextAdminId++, DEFAULT_ADMINS[i].password, ADMIN, *this);
    }

    admins[adminsCount++] = new Admin(adminName, nextAdminId++, adminPassword, "admin", *this);
}

int Bank::getAccountsCount() const
{
    return accountsCount;
}

int Bank::getCustomersCount() const
{
    return customersCount;
}

Customer *Bank::addCustomer(const std::string &name, const std::string &password)
{
    Customer *newCustomer = nullptr;

    if (customersCount < MAX_CUSTOMERS)
    {
        int customerId = nextCustomerId++;
        newCustomer = new Customer(name, customerId, password, CUSTOMER);
        customers[customersCount++] = newCustomer;
    }

    return newCustomer;
}

Customer *Bank::getCustomerById(int id)
{
    Customer *customer = nullptr;
    for (int i = 0; i < customersCount; i++)
    {
        if (customers[i]->getUserId() == id)
        {
            customer = customers[i];
            break;
        }
    }
    return customer;
}

Customer *Bank::getCustomerByCredentials(int id, const std::string &password)
{
    Customer *customer = getCustomerById(id);
    if (!customer || customer->getPassword() != password)
    {
        customer = nullptr;
    }
    return customer;
}

IAccount *Bank::addAccount(Customer &customer, double balance, const std::string &accountType)
{
    Account *newAccount = nullptr;

    if (accountsCount < MAX_ACCOUNTS)
    {
        int accountId = nextAccountId++;
        newAccount = new Account(accountId, balance, accountType, customer.getUserId());
        accounts[accountsCount++] = newAccount;
    }

    return newAccount;
}

bool Bank::removeAccount(long accountNumber, int customerId)
{
    bool success = false;
    IAccount *account = getAccount(accountNumber, customerId);
    for (int i = 0; i < accountsCount; i++)
    {
        if (accounts[i] == account)
        {
            success = true;
            delete accounts[i];

            for (int j = i; j < accountsCount - 1; j++)
            {
                accounts[j] = accounts[j + 1];
            }
            accounts[accountsCount - 1] = nullptr;
            accountsCount--;
        }
    }
    return success;
}

void Bank::removeAccountsByCustomerId(int customerId)
{
    int j = 0;
    while (j < accountsCount)
    {
        if (accounts[j] && accounts[j]->getCustomerId() == customerId)
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
}

void Bank::removeCustomerById(int id)
{
    for (int i = 0; i < customersCount; i++)
    {
        if (customers[i] && customers[i]->getUserId() == id)
        {
            removeAccountsByCustomerId(id);

            delete customers[i];

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

Admin *Bank::getAdminByCredentials(int id, const std::string &password)
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

int Bank::deposit(long accountNumber, int customerId, double amount)
{
    int errorCode;
    IAccount *account = getAccount(accountNumber, customerId);
    if (account)
    {
        if (account->addBalance(amount))
        {
            errorCode = DEPOSIT_SUCCESS_CODE;
        }
        else
        {
            errorCode = TRANSACTION_LIMIT_EXCEEDED;
        }
    }
    else
    {
        errorCode = ACCOUNT_NOT_FOUND_CODE;
    }
    return errorCode;
}

int Bank::withdraw(long accountNumber, int customerId, double amount)
{
    int errorCode;
    IAccount *account = getAccount(accountNumber, customerId);
    if (account)
    {
        if (account->getBalance() >= amount)
        {
            if (account->subtractBalance(amount))
            {
                errorCode = WITHDRAW_SUCCESS_CODE;
            }
            else
            {
                errorCode = TRANSACTION_LIMIT_EXCEEDED;
            }
        }
        else
        {
            errorCode = INSUFFICIENT_BALANCE_CODE;
        }
    }
    else
    {
        errorCode = ACCOUNT_NOT_FOUND_CODE;
    }
    return errorCode;
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

bool Bank::addAccountRequest(int customerId, double balance, const std::string &accountType)
{
    bool success = false;
    if (requestsCount < MAX_REQUESTS)
    {
        requests[requestsCount++] = new AccountRequest(customerId, balance, accountType);
        success = true;
    }
    return success;
}

AccountRequest **Bank::getAllRequests()
{
    return requests;
}

int Bank::getRequestCount() const
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

Bank::~Bank()
{
    for (int i = 0; i < accountsCount; i++)
        delete accounts[i];
    for (int i = 0; i < customersCount; i++)
        delete customers[i];
    for (int i = 0; i < adminsCount; i++)
        delete admins[i];
    for (int i = 0; i < requestsCount; i++)
        delete requests[i];
}
