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
    int accountsCount = 0;
    int customersCount = 0;
    int requestsCount = 0;

public:
    Bank();
    int getAccountsCount();
    int getCustomersCount();
    IAccount *addAccount(Customer &customer, double balance, const std::string &accountType);
    void removeAccount(IAccount *account);
    IAccount *getAccount(long accountNumber, int customerId);
    IAccount **getAllAccounts();
    Customer *addCustomer(std::string &name, std::string &password);
    Customer *findCustomerById(int id);
    Customer *findCustomerByCredentials(int id, const std::string &password);
    Admin *findAdminByCredentials(int id, const std::string &password);
    void removeCustomerById(int id);
    Customer **getAllCustomers();
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
