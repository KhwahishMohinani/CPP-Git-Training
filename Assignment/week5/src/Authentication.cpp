#include "../include/IBank.h"
#include "../include/Authentication.h"

User *Authentication::login(IBank &bank, int id, std::string pass)
{
    return bank.findUserByCredentials(id, pass);
}
