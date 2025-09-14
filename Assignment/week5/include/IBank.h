#ifndef IBANK_H
#define IBANK_H

#include <string>

class User;
class IAccount;

class IBank
{
private:
    int bankId;
    std::string bankName;
    std::string address;

public:
    virtual void addAccount(User *loggedInUser) = 0;
    virtual void removeAccount(IAccount *account) = 0;
    virtual void addUser() = 0;
    virtual User *findUserById(int id) = 0;
    virtual User *findUserByCredentials(int id, const std::string &password) = 0;
    virtual IAccount *getAccount(long accountNumber, int customerId) = 0;
    virtual IAccount *getAccountByAccountNumber(long accountNumber) = 0;
    virtual void removeUser() = 0;
    virtual void showAllAccounts() = 0;

    virtual ~IBank() = default;
};

#endif
