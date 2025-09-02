#include <iostream>
#include "operations.h"

bool isValidForAddition(const Matrix &matrix1, const Matrix &matrix2)
{
    if (matrix1.rows == matrix2.rows && matrix1.columns == matrix2.columns)
        return true;
    return false;
}

bool isValidForMultiplication(const Matrix &matrix1, const Matrix &matrix2)
{
    if (matrix1.columns == matrix2.rows)
        return true;
    return false;
}

void performAddition(const Matrix &matrix1, const Matrix &matrix2, Matrix &resultMatrix)
{
    createMatrix(matrix1.rows, matrix1.columns, resultMatrix);
    for (int i = 0; i < matrix1.rows; i++)
    {
        for (int j = 0; j < matrix1.columns; j++)
        {
            resultMatrix.data[i][j] = matrix1.data[i][j] + matrix2.data[i][j];
        }
    }
}

void performMultiplication(const Matrix &matrix1, const Matrix &matrix2, Matrix &resultMatrix)
{
    createMatrix(matrix1.rows, matrix2.columns, resultMatrix);
    for (int i = 0; i < matrix1.rows; i++)
    {
        for (int j = 0; j < matrix2.columns; j++)
        {
            resultMatrix.data[i][j] = 0;
            for (int k = 0; k < matrix1.columns; k++)
            {
                resultMatrix.data[i][j] += matrix1.data[i][k] * matrix2.data[k][j];
            }
        }
    }
}

Matrix executeOperation(char opr, const Matrix &matrix1, const Matrix &matrix2)
{
    Matrix resultMatrix = {nullptr, 0, 0};
    switch (opr)
    {
    case '+':
    {
        if (!isValidForAddition(matrix1, matrix2))
        {
            std::cout << "Cannot perform addition. Both matrices should have same dimensions\n";
        }
        else
        {
            performAddition(matrix1, matrix2, resultMatrix);
        }
        break;
    }
    case '*':
    {
        if (!isValidForMultiplication(matrix1, matrix2))
        {
            std::cout << "Cannot perform multiplication. Columns of first matrix should be equal to rows of second matrix\n";
        }
        else
        {
            performMultiplication(matrix1, matrix2, resultMatrix);
        }
        break;
    }
    default:
    {
        std::cout << "Invalid Operator\n";
        break;
    }
    }
    return resultMatrix;
}
