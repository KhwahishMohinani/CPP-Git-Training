#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include "User.h"

class Admin : public User
{
public:
    Admin(int userId, std::string password, std::string type);
    /*createAccount();
    closeAccount();
    showAccounts();
    createUser();
    deleteUser();
    displayMiniStatement();
    displayBankStatement();*/
};

#endif
