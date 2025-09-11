#include <iostream>
#include <limits>
#include "InputHandler.h"

bool isValidDouble(double &value)
{
    bool isValid = true;
    std::cin >> value;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        isValid = false;
    }
    return isValid;
}

bool isValidInt(const std::string &input, int &value)
{
    bool isValid = true;
    if (input.empty())
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
