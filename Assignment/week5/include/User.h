#ifndef USER_H
#define USER_H

#include <string>

class User
{
private:
    int userId;
    std::string password;
    std::string type;
    std::string name;

public:
    User(std::string name, int userId, std::string password, std::string type);
    void setUserId(int);
    void setPassword(std::string);
    void setType(std::string);
    void setName(std::string);
    int getUserId();
    std::string getPassword();
    std::string getType();
    std::string getName();
};

#endif
