#ifndef MATRIX_H
#define MATRIX_H

struct matrix
{
    int **data;
    int rows;
    int columns;
};

void getDimensions(int &rows, int &columns);
matrix createMatrix(int rows, int columns);
void getValues(matrix &m);
void printValues(const matrix &m);
matrix prepareMatrix();
void getOperator(char &opr);
bool isValidForAddition(const matrix &m1, const matrix &m2);
bool isValidForMultiplication(const matrix &m1, const matrix &m2);
matrix performAddition(const matrix &m1, const matrix &m2);
matrix performMultiplication(const matrix &m1, const matrix &m2);
matrix executeOperation(char opr, const matrix &m1, const matrix &m2);
void deleteMatrix(matrix &m);

#endif