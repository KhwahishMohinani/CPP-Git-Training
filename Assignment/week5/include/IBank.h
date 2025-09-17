#ifndef IBANK_H
#define IBANK_H

#include <string>

class Customer;
class IAccount;
class Admin;

class IBank
{
private:
    int bankId;
    std::string bankName;
    std::string address;

public:
    virtual int getAccountsCount() = 0;
    virtual int getCustomersCount() = 0;
    virtual IAccount *addAccount(Customer &customer, const std::string &accountType) = 0;
    virtual void removeAccount(IAccount *account) = 0;
    virtual IAccount *getAccount(long accountNumber, int customerId) = 0;
    virtual IAccount **getAllAccounts() = 0;
    virtual Customer *addCustomer(std::string &name, std::string &password) = 0;
    virtual Customer *findCustomerById(int id) = 0;
    virtual Customer *findCustomerByCredentials(int id, const std::string &password) = 0;
    virtual Admin *findAdminByCredentials(int id, const std::string &password) = 0;
    virtual void removeCustomerById(int id) = 0;
    virtual Customer **getAllCustomers() = 0;

    virtual ~IBank() = default;
};

#endif
