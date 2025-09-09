#include <iostream>
#include "matrix.h"
#include "validity.h"

Matrix::Matrix(int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;
    data = new double *[rows];
    for (int i = 0; i < rows; i++)
    {
        data[i] = new double[this->columns];
    }
}

void Matrix::setElements()
{
    Validity validity;
    double value;
    std::cout << "Enter the values of the matrix\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            while (!validity.isValidDouble(value))
            {
                std::cout << "Invalid input. Please enter a valid number: ";
            }
            data[i][j] = value;
        }
    }
}

void Matrix::getElements()
{
    std::cout << "Matrix:\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            std::cout << data[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

int Matrix::getRows() const
{
    return rows;
}

int Matrix::getColumns() const
{
    return columns;
}

bool isValidForAddition(const Matrix &matrix1, const Matrix &matrix2)
{
    return (matrix1.getRows() == matrix2.getRows() && matrix1.getColumns() == matrix2.getColumns());
}

bool isValidForMultiplication(const Matrix &matrix1, const Matrix &matrix2)
{
    return (matrix1.getColumns() == matrix2.getRows());
}

Matrix *Matrix::operator+(const Matrix &matrix2)
{
    Matrix *resultMatrixPtr = nullptr;
    if (!isValidForAddition(*this, matrix2))
    {
        std::cout << "Cannot perform addition. Both matrices should have same dimensions\n";
    }
    else
    {
        resultMatrixPtr = new Matrix(rows, columns);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                resultMatrixPtr->data[i][j] = data[i][j] + matrix2.data[i][j];
            }
        }
    }
    return resultMatrixPtr;
}

Matrix *Matrix::operator*(const Matrix &matrix2)
{
    Matrix *resultMatrixPtr = nullptr;
    if (!isValidForMultiplication(*this, matrix2))
    {
        std::cout << "Cannot perform multiplication. Columns of first matrix should be equal to rows of second matrix\n";
    }
    else
    {
        resultMatrixPtr = new Matrix(rows, matrix2.columns);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < matrix2.columns; j++)
            {
                resultMatrixPtr->data[i][j] = 0;
                for (int k = 0; k < columns; k++)
                {
                    resultMatrixPtr->data[i][j] += data[i][k] * matrix2.data[k][j];
                }
            }
        }
    }
    return resultMatrixPtr;
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] data[i];
    }
    delete[] data;
    data = nullptr;
    rows = 0;
    columns = 0;
}
