#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "IInputHandler.h"

class InputHandler : public IInputHandler
{
public:
    bool isValidInt(const std::string &input, int &value);
};

#endif
