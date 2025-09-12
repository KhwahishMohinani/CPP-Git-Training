#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <string>
class IBank;
class User;

class Authentication
{
public:
    User *login(IBank &bank, int userId, std::string password);
};

#endif
