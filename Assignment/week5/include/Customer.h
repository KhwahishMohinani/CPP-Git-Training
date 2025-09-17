#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "User.h"

class IAccount;

class Customer : public User
{
public:
    Customer(std::string name, int userId, std::string password, std::string type);
};

#endif
