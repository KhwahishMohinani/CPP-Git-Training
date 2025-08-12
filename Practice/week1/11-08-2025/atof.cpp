#include <iostream>
#include <cmath>
using namespace std;

double atof_func(string str)
{
    double num = 0.0;
    double result;
    double frac = 0.0;
    double count_after_point = 0.0;
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
                frac = frac * 10 + digit;
                count_after_point++;
            }
        }
        else
        {
            cout << "Invalid Input";
        }
    }
    frac = frac / (pow(10, count_after_point));
    result = num + frac;
    if (isNegative)
        result = -result;
    return result;
}

int main()
{
    string str = "387569.086";
    double ans = atof_func(str);
    cout << ans << endl;
    return 0;
}