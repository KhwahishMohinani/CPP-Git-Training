#ifndef INPUT_H
#define INPUT_H

#include "matrix.h"

int getValidInt();
void getDimensions(int &rows, int &columns);
void getValues(Matrix &matrix);
void prepareMatrix(Matrix &matrix);
void getOperator(char &opr);

#endif
