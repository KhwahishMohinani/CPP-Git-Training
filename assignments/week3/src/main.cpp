#include <iostream>
#include "matrix.h"
#include "input.h"
#include "operations.h"
#include "print.h"

int main()
{
    char opr;
    Matrix matrix1;
    prepareMatrix(matrix1);
    printValues(matrix1);
    std::cout << "For second matrix\n";
    Matrix matrix2;
    prepareMatrix(matrix2);
    printValues(matrix2);
    getOperator(opr);
    Matrix resultMatrix = executeOperation(opr, matrix1, matrix2);

    if (resultMatrix.data != nullptr)
    {
        printValues(resultMatrix);
        deleteMatrix(resultMatrix);
    }

    deleteMatrix(matrix1);
    deleteMatrix(matrix2);
    return 0;
}
