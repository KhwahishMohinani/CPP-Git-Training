#include "../include/matrix.h"
#include "../include/validity.h"

bool Validity::isValidForAddition(const Matrix &matrix1, const Matrix &matrix2)
{
    return (matrix1.getRows() == matrix2.getRows() && matrix1.getColumns() == matrix2.getColumns());
}

bool Validity::isValidForMultiplication(const Matrix &matrix1, const Matrix &matrix2)
{
    return (matrix1.getColumns() == matrix2.getRows());
}