#include "../include/matrix.h"

class Validity
{
public:
    bool isValidForAddition(const Matrix &matrix1, const Matrix &matrix2);
    bool isValidForMultiplication(const Matrix &matrix1, const Matrix &matrix2);
};