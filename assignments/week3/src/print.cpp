#include <iostream>
#include "print.h"

void printValues(const Matrix &matrix)
{
    std::cout << "Matrix:\n";
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.columns; j++)
        {
            std::cout << matrix.data[i][j] << "\t";
        }
        std::cout << "\n";
    }
}
