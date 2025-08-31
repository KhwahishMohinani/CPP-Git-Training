#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "matrix.h"

bool isValidForAddition(const matrix &m1, const matrix &m2);
bool isValidForMultiplication(const matrix &m1, const matrix &m2);
matrix performAddition(const matrix &m1, const matrix &m2);
matrix performMultiplication(const matrix &m1, const matrix &m2);
matrix executeOperation(char opr, const matrix &m1, const matrix &m2);

#endif