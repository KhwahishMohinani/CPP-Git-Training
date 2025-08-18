#include <iostream>
#include <cmath>
#include <stdlib.h>

void skipSpacesAndCheckSign(const char *str, int &index, bool &isNegative)
{
    while (str[index] != '\0' && str[index] == ' ')
    {
        index++;
    }
    if (str[index] != '\0' && (str[index] == '-' || str[index] == '+'))
    {
        if (str[index] == '-')
            isNegative = true;
        index++;
    }
}

bool checkSpecialValues(const char *str, int index, double &result)
{
    std::string lower = "";
    for (int j = index; j < index + 3; j++)
        lower += str[j];
    if (lower == "inf")
    {
        result = INFINITY;
        return true;
    }
    if (lower == "nan")
    {
        result = NAN;
        return true;
    }
    return false;
}

double atof_func(const char *str)
{
    double integerPart = 0.0;
    double result;
    double fractionalPart = 0.0;
    double exponentValue = 0.0;
    double decimalCount = 0.0;
    double divisor = 10.0;
    bool isNegative = false;
    bool isAfterDecimal = false;
    bool isInExponent = false;
    bool isNegExponent = false;
    bool hasDigits = false;
    int index = 0;

    skipSpacesAndCheckSign(str, index, isNegative);

    if (checkSpecialValues(str, index, result))
    {
        if (isNegative)
            return -result;
        else
            return result;
    }

    while (str[index] != '\0')
    {
        char c = str[index];
        if (isAfterDecimal == false && c == '.')
        {
            isAfterDecimal = true;
        }
        else if ((c == 'e' || c == 'E') && isInExponent == false)
        {
            isInExponent = true;
            if (str[index + 1] != '\0' && (str[index + 1] == '-' || str[index + 1] == '+'))
            {
                if (str[index + 1] == '-')
                    isNegExponent = true;
                index++;
            }
        }
        else if (c >= '0' && c <= '9')
        {
            hasDigits = true;
            int digit = c - '0';
            if (isInExponent == false)
            {
                if (isAfterDecimal == false)
                {
                    integerPart = integerPart * 10 + digit;
                }
                else
                {
                    fractionalPart = fractionalPart * 10 + digit;
                    decimalCount++;
                }
            }
            else
            {
                exponentValue = exponentValue * 10 + digit;
            }
        }
        else
        {
            break;
        }
        index++;
    }

    if (hasDigits == false)
        return 0.0;

    fractionalPart = fractionalPart / (pow(10, decimalCount));
    result = integerPart + fractionalPart;
    if (isInExponent)
    {
        if (isNegExponent)
            exponentValue = -exponentValue;
        result = result * pow(10, exponentValue);
    }
    if (isNegative)
        result = -result;
    return result;
}

int main()
{
    char input[100];
    std::cout << "Enter the string: ";
    std::cin >> input;
    const char *str = input;
    double ans = atof_func(str);
    std::cout << ans << "\n";
    double result = atof(str);
    std::cout << result << "\n";
    return 1;
}