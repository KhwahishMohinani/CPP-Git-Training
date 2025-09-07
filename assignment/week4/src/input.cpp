#include <iostream>
#include "matrix.h"
#include "validity.h"

void inputDimensions(int &rows, int &columns)
{
    Validity validity;
    std::string input;
    int value;

    std::cout << "Enter the number of rows: ";
    while (true)
    {
        std::cin >> input;
        if (validity.isValidInt(input, value))
        {
            rows = value;
            break;
        }
        else
        {
            std::cout << "Invalid input. Please enter a positive integer: ";
        }
    }

    std::cout << "Enter the number of columns: ";
    while (true)
    {
        std::cin >> input;
        if (validity.isValidInt(input, value))
        {
            columns = value;
            break;
        }
        else
        {
            std::cout << "Invalid input. Please enter a positive integer: ";
        }
    }
}

void inputOperator(char &opr)
{
    while (true)
    {
        std::cout << "Enter the Operation\n";
        std::cout << "For Addition, enter '+'\n";
        std::cout << "For Multiplication, enter '*'\n";
        std::cout << "To quit, enter 'q'\n";
        std::cin >> opr;

        if (opr == '+' || opr == '*' || opr == 'q' || opr == 'Q')
        {
            return;
        }
        else
        {
            std::cout << "Invalid operator. Please try again.\n";
        }
    }
}
