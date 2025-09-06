#include <iostream>
#include "../include/matrix.h"
#include "../include/validity.h"

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

    Matrix *resultMatrixPtr;
    while (true)
    {
        char opr;
        inputOperator(opr);
        if (opr == 'q' || opr == 'Q')
            break;

        switch (opr)
        {
        case '+':
        {
            resultMatrixPtr = matrix1 + matrix2;
            break;
        }
        case '*':
        {
            resultMatrixPtr = matrix1 * matrix2;
            break;
        }
        }
        if (resultMatrixPtr != nullptr)
        {
            resultMatrixPtr->printValues();
        }
    }
    delete resultMatrixPtr;
}
