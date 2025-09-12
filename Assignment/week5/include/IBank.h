#ifndef IBANK_H
#define IBANK_H

#include <string>

class User;

class IBank
{
private:
    int bankId;
    std::string bankName;
    std::string address;

public:
    // virtual void getBankDetails();
    virtual void addAccount(User *loggedIn) = 0;
    /*virtual void removeAccount() = 0;
    virtual void showAccount() = 0;*/
    virtual void addUser(std::string type) = 0;
    // virtual void removeUser() = 0;
    virtual User *findUserByCredentials(int id, const std::string &password) = 0;
};

#endif
