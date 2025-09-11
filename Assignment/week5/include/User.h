#ifndef USER_H
#define USER_H

#include "iostream"

class User
{
private:
    int userId;
    std::string password;
    std::string name;
    std::string email;
    int contact;

public:
    signUp();
    login();
    logout();
    showUserDetails();
};

#endif