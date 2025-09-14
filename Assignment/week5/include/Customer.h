#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "User.h"
#include "IAccount.h"

class Customer : public User
{
private:
    std::string name;
    std::string email;
    int contact;

public:
    Customer(std::string name, std::string email, int contact, int userId, std::string password, std::string type);
    void deposit(IAccount *account, double amount);
    void withdraw(IAccount *account, double amount);
    void showMenu(IBank &bank);
    /*deposit();
    withdraw();
    displayMiniStatement();
    displayBankStatement();*/
};

#endif
