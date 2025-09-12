#include "../include/Customer.h"

Customer::Customer(std::string name, std::string email, int contact, int userId, std::string password, std::string type)
{
    this->name = name;
    this->email = email;
    this->contact = contact;
    setUserId(userId);
    setPassword(password);
    setType(type);
}
