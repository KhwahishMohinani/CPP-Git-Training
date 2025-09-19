#include "AccountRequest.h"

AccountRequest::AccountRequest(int id, double balance, std::string type)
    : customerId(id), initialBalance(balance), type(type)
{
}
