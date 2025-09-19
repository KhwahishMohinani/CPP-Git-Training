#ifndef IUSER_H
#define IUSER_H

#include <string>

class IUser
{

public:
    virtual void setUserId(int) = 0;
    virtual void setType(std::string) = 0;
    virtual void setName(std::string) = 0;
    virtual int getUserId() = 0;
    virtual std::string getType() = 0;
    virtual std::string getName() = 0;
};

#endif
