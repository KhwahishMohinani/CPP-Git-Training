#include <iostream>
#include "matrix.h"
#include "input.h"
#include "operations.h"
#include "print.h"

int main()
{
    char opr;
    matrix m1 = prepareMatrix();
    std::cout << "For second matrix\n";
    matrix m2 = prepareMatrix();
    getOperator(opr);
    matrix resultMatrix = executeOperation(opr, m1, m2);

    if (resultMatrix.data != nullptr)
    {
        printValues(resultMatrix);
        deleteMatrix(resultMatrix);
    }

    deleteMatrix(m1);
    deleteMatrix(m2);
    return 0;
}