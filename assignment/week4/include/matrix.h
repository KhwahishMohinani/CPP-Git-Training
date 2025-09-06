#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
private:
    int m_rows;
    int m_columns;
    double **m_data;

public:
    Matrix(int rows, int columns);
    void setValues();
    void printValues();
    int getRows() const;
    int getColumns() const;
    Matrix *operator+(const Matrix &matrix2);
    Matrix *operator*(const Matrix &matrix2);
    ~Matrix();
};

#endif
