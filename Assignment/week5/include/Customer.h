#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "User.h"

class Customer : public User
{
private:
    std::string name;
    std::string email;
    int contact;

public:
    Customer(std::string name, std::string email, int contact, int userId, std::string password, std::string type);
    /*deposit();
    withdraw();
    displayMiniStatement();
    displayBankStatement();*/
};

#endif
