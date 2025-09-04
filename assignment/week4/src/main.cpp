#include <iostream>
#include "matrix.h"

void getDimensions(int &rows, int &columns)
{
    std::cout << "Enter the number of rows: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns: ";
    std::cin >> columns;
}

void getOperator(char &operator)
{
    while (true)
    {
        std::cout << "Enter the Operation\n";
        std::cout << "For Addition, enter '+'\n";
        std::cout << "For Multiplication, enter '*'\n";
        std::cout << "To quit, enter 'q'\n";
        std::cin >> opr;

        if (operator== '+' || operator== '*' || operator== 'q')
        {
            return;
        }
        else
        {
            std::cout << "Invalid operator. Please try again.\n";
        }
    }
}

int main()
{
    int rows, columns;

    std::cout << "For first matrix\n" getDimensions(rows, columns);
    Matrix matrix1(rows, columns);
    matrix1.printValues();

    std::cout << "For second matrix\n" getDimensions(rows, columns);
    Matrix matrix2(rows, columns);
    matrix2.printValues();

    char operator;
    getOperator(operator);
    switch (operator)
    {
    case '+':
        Matrix.performAddition(matrix1, matrix2);
    case '*':
    }
}