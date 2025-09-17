#ifndef BANK_H
#define BANK_H

#include "IBank.h"
#define MAX_CUSTOMERS 100
#define MAX_ADMINS 100
#define MAX_ACCOUNTS 100

class Bank : public IBank
{
private:
    Customer *customers[MAX_CUSTOMERS];
    Admin *admins[MAX_ADMINS];
    IAccount *accounts[MAX_ACCOUNTS];
    int adminsCount = 0;
    int accountsCount = 0;
    int customersCount = 0;

public:
    Bank();
    int getAccountsCount();
    int getCustomersCount();
    IAccount *addAccount(Customer &customer, const std::string &accountType);
    void removeAccount(IAccount *account);
    IAccount *getAccount(long accountNumber, int customerId);
    IAccount **getAllAccounts();
    Customer *addCustomer(std::string &name, std::string &password);
    Customer *findCustomerById(int id);
    Customer *findCustomerByCredentials(int id, const std::string &password);
    Admin *findAdminByCredentials(int id, const std::string &password);
    void removeCustomerById(int id);
    Customer **getAllCustomers();
};

#endif
