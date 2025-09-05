#include <iostream>
#include "../include/matrix.h"

void inputDimensions(int &rows, int &columns)
{
    std::cout << "Enter the number of rows: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns: ";
    std::cin >> columns;
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

        if (opr == '+' || opr == '*' || opr == 'q')
        {
            return;
        }
        else
        {
            std::cout << "Invalid operator. Please try again.\n";
        }
    }
}

bool isValidForAddition(const Matrix &matrix1, const Matrix &matrix2)
{
    return (matrix1.getRows() == matrix2.getRows() && matrix1.getColumns() == matrix2.getColumns());
}

bool isValidForMultiplication(const Matrix &matrix1, const Matrix &matrix2)
{
    return (matrix1.getColumns() == matrix2.getRows());
}

int main()
{
    int rows, columns;

    std::cout << "For first matrix\n";
    inputDimensions(rows, columns);
    Matrix matrix1(rows, columns);
    matrix1.setValues();
    matrix1.printValues();

    std::cout << "For second matrix\n";
    inputDimensions(rows, columns);
    Matrix matrix2(rows, columns);
    matrix2.setValues();
    matrix2.printValues();

    char opr;
    inputOperator(opr);
    switch (opr)
    {
    case '+':
    {
        if (isValidForAddition(matrix1, matrix2))
        {
            Matrix resultMatrix = matrix1 + matrix2;
            resultMatrix.printValues();
        }
        else
        {
            std::cout << "Cannot perform addition. Both matrices should have same dimensions\n";
        }
        break;
    }
    case '*':
    {
        if (isValidForMultiplication(matrix1, matrix2))
        {
            Matrix resultMatrix = matrix1 * matrix2;
            resultMatrix.printValues();
        }
        else
        {
            "Cannot perform multiplication. Columns of first matrix should be equal to rows of second matrix\n";
        }
        break;
    }
    }
}