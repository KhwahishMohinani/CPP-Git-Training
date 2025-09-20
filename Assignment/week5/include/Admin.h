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
    void deleteCustomer(int customerId);
    bool deleteAccount(long accountNumber, int customerId);
    int createAccount(Customer &customer, double balance, std::string &accountType);
    int handleRequests();
};

#endif
