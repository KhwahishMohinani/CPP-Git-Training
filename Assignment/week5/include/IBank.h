#ifndef IBANK_H
#define IBANK_H

#include <string>

class Customer;
class IAccount;
class Admin;
class Transaction;
struct AccountRequest;

class IBank
{
public:
    virtual int getAccountsCount() const = 0;
    virtual int getCustomersCount() const = 0;
    virtual IAccount *addAccount(Customer &customer, double balance, const std::string &accountType) = 0;
    virtual bool removeAccount(long accountNumber, int customerId) = 0;
    virtual IAccount *getAccount(long accountNumber, int customerId) = 0;
    virtual IAccount **getAllAccounts() = 0;
    virtual Customer *addCustomer(std::string &name, std::string &password) = 0;
    virtual Customer *getCustomerById(int id) = 0;
    virtual Customer *getCustomerByCredentials(int id, const std::string &password) = 0;
    virtual Admin *getAdminByCredentials(int id, const std::string &password) = 0;
    virtual void removeAccountsByCustomerId(int customerId) = 0;
    virtual void removeCustomerById(int id) = 0;
    virtual Customer **getAllCustomers() = 0;
    virtual bool deposit(long accountNumber, int customerId, double amount) = 0;
    virtual bool withdraw(long accountNumber, int customerId, double amount) = 0;
    virtual Transaction **getAccountTransactions(long accountNumber, int userId) = 0;
    virtual int getAccountTransactionsCount(long accountNumber, int userId) = 0;
    virtual double getAccountBalance(long accountNumber, int customerId) = 0;
    virtual bool addAccountRequest(int customerId, double balance, std::string type) = 0;
    virtual AccountRequest **getAllRequests() = 0;
    virtual int getRequestCount() const = 0;
    virtual void clearRequests() = 0;
    virtual IAccount **getAccountsByCustomerId(int customerId, int &accountCount) = 0;
    virtual ~IBank() {};
};

#endif
