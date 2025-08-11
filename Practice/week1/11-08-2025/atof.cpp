#include <iostream>
using namespace std;

double atof_func(string str)
{
    double num = 0.0;
    double result;
    double frac = 0.0;
    double divisor = 10.0;
    bool isNegative = false;
    bool afterDecimal = false;
    for (int i = 0; i < str.length(); i++)
    {
        char c = str[i];
        if (c == '-')
        {
            isNegative = true;
        }
        else if (c == '.')
        {
            afterDecimal = true;
        }
        else if (c >= '0' && c <= '9')
        {
            int digit = c - '0';
            if (afterDecimal == false)
            {
                num = num * 10 + digit;
            }
            else
            {
                frac = frac + digit / divisor;
                divisor = divisor * 10;
            }
        }
        else
        {
            cout << "Invalid Input";
        }
    }
    result = num + frac;
    return result;
}

int main()
{
    string str = "3.086";
    double ans = atof_func(str);
    cout << ans;
    return 0;
}