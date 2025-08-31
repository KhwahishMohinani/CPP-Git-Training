#ifndef INPUT_H
#define INPUT_H

#include "matrix.h"

int getValidInt();
void getDimensions(int &rows, int &columns);
void getValues(matrix &m);
matrix prepareMatrix();
void getOperator(char &opr);

#endif