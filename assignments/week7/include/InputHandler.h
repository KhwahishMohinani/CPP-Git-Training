#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <string>

class InputHandler
{
public:
    bool isValidDouble(std::istream &input, double &value);
    bool isValidInt(const std::string &input, int &value);
    bool isValidLong(const std::string &input, long &value);
};

#endif
