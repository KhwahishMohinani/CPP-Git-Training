#include <iostream>
#include <limits>
#include "InputHandler.h"

bool InputHandler::isValidDouble(std::istream &input, double &value)
{
    bool isValid = true;
    input >> value;

    if (input.fail())
    {
        input.clear();
        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        isValid = false;
    }
    return isValid;
}

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

bool InputHandler::isValidLong(const std::string &input, long &value)
{
    bool isValid = true;
    if (input.empty())
        isValid = false;
    else
    {
        long number = 0;
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
