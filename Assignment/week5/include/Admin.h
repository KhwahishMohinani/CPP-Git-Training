#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include "User.h"

class IBank;
class IAccount;
class Customer;

class Admin : public User
{
    IBank &bank;

public:
    Admin(std::string name, int userId, std::string password, std::string type, IBank &bank);
    Customer **fetchAllCustomers();
    int fetchCustomersCount();
    IAccount **fetchAllAccounts();
    int fetchAccountsCount();
    Customer *searchCustomerById(int id);
    void deleteCustomerById(int id);
    IAccount *fetchAccount(int accountNumber, int customerId);
    void deleteAccount(IAccount *account);
    Customer *createCustomer(std::string name, std::string password);
    IAccount *createAccount(Customer &customer, std::string accountType);
};

#endif
