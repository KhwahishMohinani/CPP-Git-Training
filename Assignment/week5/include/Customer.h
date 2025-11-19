#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "User.h"

class IAccount;

class Customer : public User
{
public:
    Customer(const std::string &name, int userId, const std::string &password, const std::string &userType);
};

#endif
