#include <iostream>
using namespace std;

int convertToDigit(string input)
{
    int num = 0;
    int size = input.length();
    for (int i = 0; i < size; i++)
    {
        if (input[i] >= '0' && input[i] <= '9')
        {
            int digit = input[i] - '0';
            num = num * 10 + digit;
        }
        else
        {
            return -1;
        }
    }
    return num;
}

void print_numbers(int row, int center_row, bool isUpperRight)
{
    for (int col = 0; col <= row; col++)
    {
        if (row == center_row && col == 0 && center_row % 2 == 0 && isUpperRight == true)
        {
            continue;
        }
        if (col % 2 == 0)
        {

            cout << "1 ";
        }
        else
            cout << "0 ";
    }
}

void print_spaces(int space)
{
    for (int i = 0; i < space; i++)
    {
        cout << "  ";
    }
}

void pattern(int center_row)
{
    for (int row = 0; row <= center_row; row++)
    {
        print_numbers(row, center_row, false);

        print_spaces(center_row - row);

        if (center_row % 2 == 0)
        {
            print_spaces(center_row - row - 1);
        }
        else
        {
            print_spaces(center_row - row);
        }

        print_numbers(row, center_row, true);

        cout << "\n";
    }
    for (int row = 0; row < center_row; row++)
    {
        print_numbers(center_row - row - 1, center_row, false);

        print_spaces(row + 1);

        if (center_row % 2 == 0)
        {
            print_spaces(row);
        }
        else
        {
            print_spaces(row + 1);
        }

        print_numbers(center_row - row - 1, center_row, false);

        cout << "\n";
    }
}

int main()
{
    int center_row;
    string input;
    cin >> input;
    center_row = convertToDigit(input);
    if (center_row <= 0)
        cout << "Invalid Input\n";
    else
        pattern(center_row);
    return 0;
}