#ifndef MATRIX_H
#define MATRIX_H

struct matrix
{
    double **data;
    int rows;
    int columns;
};

matrix createMatrix(int rows, int columns);
void deleteMatrix(matrix &m);

#endif