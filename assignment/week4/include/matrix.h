#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
private:
    int rows;
    int columns;
    double **data;

public:
    Matrix(int rows, int columns);
    void setElements();
    void getElements();
    int getRows() const;
    int getColumns() const;
    bool isValidForAddition(const Matrix &matrix1, const Matrix &matrix2);
    bool isValidForMultiplication(const Matrix &matrix1, const Matrix &matrix2);
    Matrix *operator+(const Matrix &matrix2);
    Matrix *operator*(const Matrix &matrix2);
    ~Matrix();
};

#endif
