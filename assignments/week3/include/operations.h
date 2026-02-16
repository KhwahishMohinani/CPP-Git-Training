#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "matrix.h"

bool isValidForAddition(const Matrix &matrix1, const Matrix &matrix2);
bool isValidForMultiplication(const Matrix &matrix1, const Matrix &matrix2);
void performAddition(const Matrix &matrix1, const Matrix &matrix2, Matrix &resultMatrix);
void performMultiplication(const Matrix &matrix1, const Matrix &matrix2, Matrix &resultMatrix);
Matrix *executeOperation(char opr, const Matrix &matrix1, const Matrix &matrix2);

#endif
