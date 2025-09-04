#include <iostream>

class Matrix
{
private:
    int m_rows;
    int m_columns;
    double **m_data;

public:
    Matrix(int rows, int columns);
    void printValues();
    ~Matrix();
};

Matrix::Matrix(int rows, int columns)
{
    m_rows = rows;
    m_columns = columns;
    m_data = new double *[rows];
    for (int i = 0; i < rows; i++)
    {
        m_data[i] = new double[columns];
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