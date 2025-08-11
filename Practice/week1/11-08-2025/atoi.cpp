#include <iostream>
#include <string>
using namespace std;

int atoi_fun(string s)
{
    int n = s.length();
    int n_num = 0, unit_pl;
    for (int i = 0; i < n; i++)
    {
        unit_pl = s[i] - '0';
        if (unit_pl > 9 && unit_pl < 0)
        {
            cout << "Invalid Input";
            return 0;
        }
        if (n - i - 1 >= 0)
        {
            n_num = n_num * 10 + unit_pl;
        }
    }
    return n_num;
}

int main()
{
    string s = "7647";
    int num = atoi_fun(s);
    cout << num;
    return 0;
}