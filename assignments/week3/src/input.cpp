#include <iostream>
#include <limits>
#include "input.h"
#include "print.h"

int getValidInt()
{
    int value;
    bool valid = false;
    do
    {
        if (std::cin >> value && value > 0)
        {
            valid = true;
        }
        else
        {
            std::cout << "Invalid input. Please enter a positive integer.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!valid);
    return value;
}

double getValidDouble()
{
    double value;
    bool valid = false;
    do
    {
        if (std::cin >> value)
        {
            valid = true;
        }
        else
        {
            std::cout << "Invalid input. Please enter a valid number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!valid);
    return value;
}

void getDimensions(int &rows, int &columns)
{
    std::cout << "Enter the number of rows: ";
    rows = getValidInt();
    std::cout << "Enter the number of columns: ";
    columns = getValidInt();
}

void getValues(matrix &m)
{
    std::cout << "Enter the values of the matrix\n";
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.columns; j++)
        {
            m.data[i][j] = getValidDouble();
        }
    }
}

matrix prepareMatrix()
{
    int rows, columns;
    getDimensions(rows, columns);
    matrix m = createMatrix(rows, columns);
    getValues(m);
    printValues(m);
    return m;
}

void getOperator(char &opr)
{
    while (true)
    {
        std::cout << "Enter the Operation\n";
        std::cout << "For Addition, enter '+'\n";
        std::cout << "For Multiplication, enter '*'\n";
        std::cin >> opr;

        if (opr == '+' || opr == '*')
        {
            return;
        }
        else
        {
            std::cout << "Invalid operator. Please try again.\n";
        }
    }
}
