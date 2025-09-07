#include <iostream>
#include "matrix.h"
#include "validity.h"
#include "input.h"

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
            delete resultMatrixPtr;
            resultMatrixPtr = nullptr;
        }
    }
}
