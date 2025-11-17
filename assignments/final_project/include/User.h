#ifndef USER_H
#define USER_H

#include <string>
#include <map>
#include "IPost.h"
#include "IUser.h"

class User : public IUser
{
private:
    std::string username;
    std::string password;
    std::string fullName;

public:
    User(const std::string &username, const std::string &password, const std::string &fullName);
    std::string getUsername();
    std::string getPassword();
    std::string getFullName();
    void setFullName(const std::string &name);
    void setPassword(const std::string &password);
};

#endif
