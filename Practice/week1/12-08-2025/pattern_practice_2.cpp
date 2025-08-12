#include <iostream>
using namespace std;

int main()
{
    int center_row;
    cin >> center_row;
    if (center_row % 2 == 0)
        center_row = center_row + 1;
    for (int row = 0; row < center_row; row++)
    {
        for (int col = 0; col <= row; col++)
        {
            if (col % 2 == 0)
                cout << "1 ";
            else
                cout << "0 ";
        }
        for (int col = row; col < center_row - 1; col++)
        {
            cout << "  ";
        }
        for (int col = row + 1; col < center_row - 1; col++)
        {
            cout << "  ";
        }
        for (int col = 0; col <= row; col++)
        {
            if (center_row % 2 == 0)
            {
                if (col % 2 == 0)
                {
                    if (row == center_row - 1 && col == 0)
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
                if (col % 2 == 0)
                {
                    if (row == center_row - 1 && col == 0)
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
    for (int row = 0; row < center_row - 1; row++)
    {
        for (int col = 0; col < center_row - 1 - row; col++)
        {
            if (col % 2 == 0)
                cout << "1 ";
            else
                cout << "0 ";
        }
        for (int col = 0; col <= row; col++)
        {
            cout << "  ";
        }
        for (int col = 1; col <= row; col++)
        {
            cout << "  ";
        }
        for (int col = 0; col < center_row - 1 - row; col++)
        {
            if (center_row % 2 == 0)
            {
                if (col % 2 == 0)
                    cout << "0 ";
                else
                    cout << "1 ";
            }
            else
            {
                if (col % 2 == 0)
                    cout << "1 ";
                else
                    cout << "0 ";
            }
        }
        cout << endl;
    }
}