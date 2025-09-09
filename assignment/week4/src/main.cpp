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
    matrix1.setElements();
    matrix1.getElements();

    std::cout << "For second matrix\n";
    inputDimensions(rows, columns);
    Matrix matrix2(rows, columns);
    matrix2.setElements();
    matrix2.getElements();

    Matrix *resultMatrixPtr = nullptr;
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
            resultMatrixPtr->getElements();
            delete resultMatrixPtr;
            resultMatrixPtr = nullptr;
        }
    }
}
