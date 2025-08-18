#include <iostream>

int convertToDigit(std::string input)
{
    int number = 0;
    int length = input.length();
    for (int i = 0; i < length; i++)
    {
        if (input[i] >= '0' && input[i] <= '9')
        {
            int digit = input[i] - '0';
            number = number * 10 + digit;
        }
        else
        {
            return -1;
        }
    }
    return number;
}

void printNumbers(int row, int center_row, bool isUpperRight)
{
    for (int col = 0; col <= row; col++)
    {
        if (row == center_row && col == 0 && center_row % 2 == 0 && isUpperRight == true)
        {
            continue;
        }
        if (col % 2 == 0)
        {

            std::cout << "1 ";
        }
        else
            std::cout << "0 ";
    }
}

void printSpaces(int space)
{
    for (int i = 0; i < space; i++)
    {
        std::cout << "  ";
    }
}

void pattern(int centerRow)
{
    for (int row = 0; row <= centerRow; row++)
    {
        printNumbers(row, centerRow, false);

        printSpaces(centerRow - row);

        if (centerRow % 2 == 0)
        {
            printSpaces(centerRow - row - 1);
        }
        else
        {
            printSpaces(centerRow - row);
        }

        printNumbers(row, centerRow, true);

        std::cout << "\n";
    }
    for (int row = 0; row < centerRow; row++)
    {
        printNumbers(centerRow - row - 1, centerRow, false);

        printSpaces(row + 1);

        if (centerRow % 2 == 0)
        {
            printSpaces(row);
        }
        else
        {
            printSpaces(row + 1);
        }

        printNumbers(centerRow - row - 1, centerRow, false);

        std::cout << "\n";
    }
}

int main()
{
    std::cout << "Enter the number of rows: ";
    int centerRow;
    std::string input;
    std::cin >> input;
    centerRow = convertToDigit(input);
    if (centerRow <= 0)
        std::cout << "Invalid Input\n";
    else
        pattern(centerRow);
    return 0;
}