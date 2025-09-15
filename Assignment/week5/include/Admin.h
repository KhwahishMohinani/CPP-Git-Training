#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include "User.h"
#include "IBank.h"

class IBank;
class IAccount;

class Admin : public User
{
public:
    Admin(int userId, std::string password, std::string type);
    void createAccount(IBank &bank);
    void closeAccount(IBank &bank);
    void createUser(IBank &bank);
    void deleteUser(IBank &bank);
    void displayAllAccounts(IBank &bank);
};

#endif
