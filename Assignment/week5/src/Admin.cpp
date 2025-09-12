#include "../include/Admin.h"

Admin::Admin(int userId, std::string password, std::string type)
{
    setUserId(userId);
    setPassword(password);
    setType(type);
}
