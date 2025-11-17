#ifndef I_INPUT_HANDLER
#define I_INPUT_HANDLER

#include <string>

class IInputHandler
{
public:
    virtual bool isValidInt(const std::string &input, int &value) = 0;
};

#endif
