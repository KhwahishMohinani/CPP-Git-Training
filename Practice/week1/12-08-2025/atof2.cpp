#include <iostream>
#include <cmath>
using namespace std;

double atof_func(string str)
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
    int i = 0;
    while (i < str.length() && str[i] == ' ')
    {
        i++;
    }
    if (i < str.length() && (str[i] == '-' || str[i] == '+'))
    {
        if (str[i] == '-')
            isNegative = true;
        i++;
    }
    while (i < str.length())
    {
        char c = str[i];
        if (afterDecimal == false && c == '.')
        {
            afterDecimal = true;
        }
        else if (c == 'e' && inExponent == false)
        {
            inExponent = true;
            if (i + 1 < str.length() && (str[i + 1] == '-' || str[i + 1] == '+'))
            {
                if (str[i + 1] == '-')
                    isNegExponent = true;
                i++;
            }
        }
        else if (c >= '0' && c <= '9')
        {
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
    string str;
    cout << "Enter the string: ";
    cin >> str;
    double ans = atof_func(str);
    cout << ans << endl;
    return 0;
}