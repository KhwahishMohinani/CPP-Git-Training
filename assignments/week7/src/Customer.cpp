#include "User.h"
#include "Customer.h"
#include "InputHandler.h"

Customer::Customer(const std::string &name, int userId, const std::string &password, const std::string &userType)
    : User(name, userId, password, userType)
{
}
