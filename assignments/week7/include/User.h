#ifndef USER_H
#define USER_H

#include <string>

class User
{
protected:
    std::string name;
    int userId;
    std::string password;
    std::string userType;

public:
    User(const std::string &name, int userId, const std::string &password, const std::string &type);
    int getUserId() const;
    std::string getPassword() const;
    std::string getUserType() const;
    std::string getName() const;
};

#endif
