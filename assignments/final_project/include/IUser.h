#ifndef I_USER_H
#define I_USER_H

class IUser
{
public:
    virtual std::string getUsername() = 0;
    virtual std::string getPassword() = 0;
    virtual std::string getFullName() = 0;
    virtual void setFullName(const std::string &name) = 0;
    virtual void setPassword(const std::string &password) = 0;
};

#endif
