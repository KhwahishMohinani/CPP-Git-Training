#ifndef IBANK_H
#define IBANK_H

#include <iostream>

class IBank
{
private:
    int bankId;
    std::string bankName;
    std::string address;

public:
    getBankDetails();
    createAccount();
    closeAccount();
    showAccount();
};

#endif