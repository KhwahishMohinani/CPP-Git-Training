#include <iostream>
#include "matrix.h"

void createMatrix(int rows, int columns, Matrix &matrix)
{
    matrix.rows = rows;
    matrix.columns = columns;
    matrix.data = new double *[rows];
    for (int i = 0; i < rows; i++)
    {
        matrix.data[i] = new double[columns];
    }
}

void deleteMatrix(Matrix &matrix)
{
    for (int i = 0; i < matrix.rows; i++)
    {
        delete[] matrix.data[i];
    }
    delete[] matrix.data;
    matrix.data = nullptr;
    matrix.rows = 0;
    matrix.columns = 0;
}
