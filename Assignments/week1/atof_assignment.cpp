#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;

double atof_func(const char *str)
{
    double num = 0.0;
    double result;
    double frac = 0.0;
    double exponent = 0.0;
    double count_after_point = 0.0;
    double divisor = 10.0;
    bool isNegative = false;
    bool afterDecimal = false;
    bool inExponent = false;
    bool isNegExponent = false;
    bool hasDigits = false;
    int i = 0;
    while (str[i] != '\0' && str[i] == ' ')
    {
        i++;
    }
    if (str[i] != '\0' && (str[i] == '-' || str[i] == '+'))
    {
        if (str[i] == '-')
            isNegative = true;
        i++;
    }

    string lower = "";
    for (int j = i; j < i + 3; j++)
        lower += str[j];
    if (lower == "inf")
    {
        if (isNegative)
            return -INFINITY;
        else
            return INFINITY;
    }
    if (lower == "nan")
    {
        if (isNegative)
            return -NAN;
        else
            return NAN;
    }

    while (str[i] != '\0')
    {
        char c = str[i];
        if (afterDecimal == false && c == '.')
        {
            afterDecimal = true;
        }
        else if ((c == 'e' || c == 'E') && inExponent == false)
        {
            inExponent = true;
            if (str[i + 1] != '\0' && (str[i + 1] == '-' || str[i + 1] == '+'))
            {
                if (str[i + 1] == '-')
                    isNegExponent = true;
                i++;
            }
        }
        else if (c >= '0' && c <= '9')
        {
            hasDigits = true;
            int digit = c - '0';
            if (inExponent == false)
            {
                if (afterDecimal == false)
                {
                    num = num * 10 + digit;
                }
                else
                {
                    frac = frac * 10 + digit;
                    count_after_point++;
                }
            }
            else
            {
                exponent = exponent * 10 + digit;
            }
        }
        else
        {
            break;
        }
        i++;
    }

    if (hasDigits == false)
        return 0.0;

    frac = frac / (pow(10, count_after_point));
    result = num + frac;
    if (inExponent)
    {
        if (isNegExponent)
            exponent = -exponent;
        result = result * pow(10, exponent);
    }
    if (isNegative)
        result = -result;
    return result;
}

int main()
{
    char input[100];
    cout << "Enter the string: ";
    cin >> input;
    const char *str = input;
    double ans = atof_func(str);
    cout << ans << endl;
    double result = atof(str);
    cout << result << endl;
    return 1;
}