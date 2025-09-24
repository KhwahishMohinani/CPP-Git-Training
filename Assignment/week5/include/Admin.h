#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include "User.h"
#include "structs.h"

class IBank;
class IAccount;
class Customer;

class Admin : public User
{
    RequestResult lastRequestResult;
    IBank &bank;

public:
    Admin(const std::string &name, int userId, const std::string &password, const std::string &type, IBank &bank);
    Customer **fetchAllCustomers();
    int fetchCustomersCount();
    IAccount **fetchAllAccounts();
    int fetchAccountsCount();
    Customer *searchCustomerById(int id);
    void deleteCustomer(int customerId);
    bool deleteAccount(long accountNumber, int customerId);
    int createAccount(Customer &customer, double balance, const std::string &accountType);
    bool handleRequests();
    RequestResult getLastResult() const;
};

#endif
