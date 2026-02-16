#ifndef MATRIX_H
#define MATRIX_H

struct Matrix
{
    double **data;
    int rows;
    int columns;
};

void createMatrix(int rows, int columns, Matrix &matrix);
void deleteMatrix(Matrix &matrix);

#endif
