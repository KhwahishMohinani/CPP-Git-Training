#ifndef USER_H
#define USER_H

class IBank;
class IAccount;

class User
{
private:
    int userId;
    std::string password;
    std::string type;

public:
    void signUp(IBank &bank);
    User *login(IBank &bank);
    void setUserId(int);
    void setPassword(std::string);
    void setType(std::string);
    int getUserId();
    std::string getPassword();
    std::string getType();
    virtual ~User() = default;
};

#endif
