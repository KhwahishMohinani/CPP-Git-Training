#include <iostream>
#include "../include/matrix.h"
#include "../include/validity.h"

Matrix::Matrix(int rows, int columns)
{
    m_rows = rows;
    m_columns = columns;
    m_data = new double *[m_rows];
    for (int i = 0; i < m_rows; i++)
    {
        m_data[i] = new double[m_columns];
    }
}

void Matrix::setValues()
{
    std::cout << "Enter the values of the matrix\n";
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_columns; j++)
        {
            std::cin >> m_data[i][j];
        }
    }
}

void Matrix::printValues()
{
    std::cout << "Matrix:\n";
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_columns; j++)
        {
            std::cout << m_data[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

int Matrix::getRows() const
{
    return m_rows;
}

int Matrix::getColumns() const
{
    return m_columns;
}

Matrix Matrix::operator+(const Matrix &matrix2)
{
    Validity validity;
    if (!validity.isValidForAddition(*this, matrix2))
    {
        std::cout << "Cannot perform addition. Both matrices should have same dimensions\n";
    }
    else
    {
        Matrix resultMatrix(m_rows, m_columns);
        for (int i = 0; i < m_rows; i++)
        {
            for (int j = 0; j < m_columns; j++)
            {
                resultMatrix.m_data[i][j] = m_data[i][j] + matrix2.m_data[i][j];
            }
        }
        return resultMatrix;
    }
}

Matrix Matrix::operator*(const Matrix &matrix2)
{
    Validity validity;
    if (!validity.isValidForMultiplication(*this, matrix2))
    {
        std::cout << "Cannot perform multiplication. Columns of first matrix should be equal to rows of second matrix\n";
    }
    else
    {
        Matrix resultMatrix(m_rows, matrix2.m_columns);
        for (int i = 0; i < m_rows; i++)
        {
            for (int j = 0; j < matrix2.m_columns; j++)
            {
                resultMatrix.m_data[i][j] = 0;
                for (int k = 0; k < m_columns; k++)
                {
                    resultMatrix.m_data[i][j] += m_data[i][k] * matrix2.m_data[k][j];
                }
            }
        }
        return resultMatrix;
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < m_rows; i++)
    {
        delete[] m_data[i];
    }
    delete[] m_data;
    m_data = nullptr;
    m_rows = 0;
    m_columns = 0;
}
