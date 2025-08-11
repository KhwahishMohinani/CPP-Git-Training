#include <iostream>
using namespace std;

int main()
{
    int half_rows = 7;
    int center;
    for (int i = 0; i < half_rows; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (j % 2 == 0)
                cout << "1 ";
            else
                cout << "0 ";
        }
        for (int j = i; j < half_rows - 1; j++)
        {
            cout << "  ";
        }
        for (int j = i + 1; j < half_rows - 1; j++)
        {
            cout << "  ";
        }
        for (int j = 0; j <= i; j++)
        {
            if (half_rows % 2 == 0)
            {
                if (j % 2 == 0)
                {
                    if (i == half_rows - 1 && j == 0)
                    {
                        continue;
                    }
                    else
                    {
                        cout << "0 ";
                    }
                }
                else
                    cout << "1 ";
            }
            else
            {
                if (j % 2 == 0)
                {
                    if (i == half_rows - 1 && j == 0)
                    {
                        continue;
                    }
                    else
                    {
                        cout << "1 ";
                    }
                }
                else
                    cout << "0 ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < half_rows - 1; i++)
    {
        for (int j = 0; j < half_rows - 1 - i; j++)
        {
            if (j % 2 == 0)
                cout << "1 ";
            else
                cout << "0 ";
        }
        for (int j = 0; j <= i; j++)
        {
            cout << "  ";
        }
        for (int j = 1; j <= i; j++)
        {
            cout << "  ";
        }
        for (int j = 0; j < half_rows - 1 - i; j++)
        {
            if (half_rows % 2 == 0)
            {
                if (j % 2 == 0)
                    cout << "0 ";
                else
                    cout << "1 ";
            }
            else
            {
                if (j % 2 == 0)
                    cout << "1 ";
                else
                    cout << "0 ";
            }
        }
        cout << endl;
    }
}