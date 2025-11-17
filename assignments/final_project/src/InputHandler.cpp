#include "InputHandler.h"

bool InputHandler::isValidInt(const std::string &input, int &value)
{
    bool isValid = true;
    if (input.empty() || input.length() > 10)
        isValid = false;
    else
    {
        int number = 0;
        for (char ch : input)
        {
            if (ch >= '0' && ch <= '9')
            {
                int digit = ch - '0';
                number = number * 10 + digit;
            }
            else
            {
                isValid = false;
                break;
            }
        }

        if (isValid && number > 0)
        {
            value = number;
        }
        else
        {
            isValid = false;
        }
    }
    return isValid;
}
