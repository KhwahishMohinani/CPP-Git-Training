#ifndef BANK_H
#define BANK_H

#include "IBank.h"
#define MAX_CUSTOMERS 100
#define MAX_ADMINS 100
#define MAX_ACCOUNTS 100
#define MAX_REQUESTS 100

class Bank : public IBank
{
private:
    int bankId;
    std::string bankName;
    Customer *customers[MAX_CUSTOMERS];
    Admin *admins[MAX_ADMINS];
    IAccount *accounts[MAX_ACCOUNTS];
    AccountRequest *requests[MAX_REQUESTS];
    int adminsCount = 0;
    int accountsCount = 0, nextAdminId = 1;
    int customersCount = 0, nextCustomerId = 1;
    ;
    int requestsCount = 0, nextAccountId = 1;

public:
    Bank();
    int getAccountsCount();
    int getCustomersCount();
    IAccount *addAccount(Customer &customer, double balance, const std::string &accountType);
    bool removeAccount(long accountNumber, int customerId);
    IAccount *getAccount(long accountNumber, int customerId);
    IAccount **getAllAccounts();
    Customer *addCustomer(std::string &name, std::string &password);
    Customer *getCustomerById(int id);
    Customer *getCustomerByCredentials(int id, const std::string &password);
    Admin *getAdminByCredentials(int id, const std::string &password);
    Customer **getAllCustomers();
    void removeAccountsByCustomerId(int customerId);
    void removeCustomerById(int id);
    bool deposit(long accountNumber, int customerId, double amount);
    bool withdraw(long accountNumber, int customerId, double amount);
    Transaction **getAccountTransactions(long accountNumber, int userId);
    int getAccountTransactionsCount(long accountNumber, int userId);
    double getAccountBalance(long accountNumber, int customerId);
    bool addAccountRequest(int customerId, double balance, std::string type);
    AccountRequest **getAllRequests();
    int getRequestCount();
    IAccount **getAccountsByCustomerId(int customerId, int &accountCount);
    void clearRequests();
};

#endif
