#ifndef BANK_H
#define BANK_H

#include "IBank.h"
#include "constants.h"

class Bank : public IBank
{
private:
    int bankId;
    std::string bankName;
    Customer *customers[MAX_CUSTOMERS];
    Admin *admins[MAX_ADMINS];
    IAccount *accounts[MAX_ACCOUNTS];
    AccountRequest *requests[MAX_REQUESTS];
    int adminsCount;
    int accountsCount, nextAdminId;
    int customersCount, nextCustomerId;
    int requestsCount, nextAccountId;

public:
    Bank(int bankId, const std::string &bankName, const std::string &adminName, const std::string &adminPassword);
    int getAccountsCount() const;
    int getCustomersCount() const;
    int getRequestCount() const;
    int getNextAccountId() const;
    bool addAccount(Customer &customer, IAccount *account);
    bool removeAccount(long accountNumber, int customerId);
    IAccount *getAccount(long accountNumber, int customerId);
    IAccount **getAllAccounts();
    Customer *addCustomer(const std::string &name, const std::string &password);
    Customer *getCustomerById(int id);
    Customer *getCustomerByCredentials(int id, const std::string &password);
    Admin *getAdminByCredentials(int id, const std::string &password);
    Customer **getAllCustomers();
    void removeAccountsByCustomerId(int customerId);
    void removeCustomerById(int id);
    int deposit(long accountNumber, int customerId, double amount);
    int withdraw(long accountNumber, int customerId, double amount);
    Transaction **getAccountTransactions(long accountNumber, int userId);
    int getAccountTransactionsCount(long accountNumber, int userId);
    double getAccountBalance(long accountNumber, int customerId);
    bool addAccountRequest(int customerId, double balance, const std::string &type);
    AccountRequest **getAllRequests();
    IAccount **getAccountsByCustomerId(int customerId, int &accountCount);
    void clearRequests();
    ~Bank();
};

#endif
