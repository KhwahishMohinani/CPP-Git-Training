#include "User.h"
#include "Customer.h"
#include "InputHandler.h"

Customer::Customer(std::string name, int userId, std::string password, std::string userType)
    : User(name, userId, password, userType)
{
}
