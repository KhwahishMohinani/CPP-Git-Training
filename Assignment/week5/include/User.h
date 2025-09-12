#ifndef USER_H
#define USER_H

class IBank;

class User
{
private:
    int userId;
    std::string password;
    std::string type;

public:
    // void signUp();
    User *login(IBank &bank);
    /*void logout();
    void showUserDetails();*/
    void setUserId(int);
    void setPassword(std::string);
    void setType(std::string);
    int getUserId();
    std::string getPassword();
    std::string getType();
};

#endif
