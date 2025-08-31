#include <iostream>
#include "print.h"

void printValues(const matrix &m)
{
    std::cout << "Matrix:\n";
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.columns; j++)
        {
            std::cout << m.data[i][j] << "\t";
        }
        std::cout << "\n";
    }
}