#include <iostream>
#include "operations.h"

bool isValidForAddition(const matrix &m1, const matrix &m2)
{
    if (m1.rows == m2.rows && m1.columns == m2.columns)
        return true;
    return false;
}

bool isValidForMultiplication(const matrix &m1, const matrix &m2)
{
    if (m1.columns == m2.rows)
        return true;
    return false;
}

matrix performAddition(const matrix &m1, const matrix &m2)
{
    matrix resultMatrix = createMatrix(m1.rows, m1.columns);
    for (int i = 0; i < m1.rows; i++)
    {
        for (int j = 0; j < m1.columns; j++)
        {
            resultMatrix.data[i][j] = m1.data[i][j] + m2.data[i][j];
        }
    }
    return resultMatrix;
}

matrix performMultiplication(const matrix &m1, const matrix &m2)
{
    matrix resultMatrix = createMatrix(m1.rows, m2.columns);
    for (int i = 0; i < m1.rows; i++)
    {
        for (int j = 0; j < m2.columns; j++)
        {
            resultMatrix.data[i][j] = 0;
            for (int k = 0; k < m1.columns; k++)
            {
                resultMatrix.data[i][j] += m1.data[i][k] * m2.data[k][j];
            }
        }
    }
    return resultMatrix;
}

matrix executeOperation(char opr, const matrix &m1, const matrix &m2)
{
    matrix resultMatrix = {nullptr, 0, 0};
    switch (opr)
    {
    case '+':
    {
        if (!isValidForAddition(m1, m2))
        {
            std::cout << "Cannot perform addition. Both matrices should have same dimensions\n";
        }
        else
        {
            resultMatrix = performAddition(m1, m2);
        }
        break;
    }
    case '*':
    {
        if (!isValidForMultiplication(m1, m2))
        {
            std::cout << "Cannot perform multiplication. Columns of first matrix should be equal to rows of second matrix\n";
        }
        else
        {
            resultMatrix = performMultiplication(m1, m2);
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