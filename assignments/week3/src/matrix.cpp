#include <iostream>
#include "matrix.h"

matrix createMatrix(int rows, int columns)
{
    matrix m;
    m.rows = rows;
    m.columns = columns;
    m.data = new double *[rows];
    for (int i = 0; i < rows; i++)
    {
        m.data[i] = new double[columns];
    }
    return m;
}

void deleteMatrix(matrix &m)
{
    for (int i = 0; i < m.rows; i++)
    {
        delete[] m.data[i];
    }
    delete[] m.data;
    m.data = nullptr;
    m.rows = 0;
    m.columns = 0;
}