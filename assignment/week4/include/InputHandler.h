#ifndef VALIDITY_H
#define VALIDITY_H

#include <string>

class InputHandler
{
public:
    bool isValidDouble(double &value);
    bool isValidInt(const std::string &input, int &value);
};

#endif
