#include <iostream>
#include <limits>
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

bool Validity::isValidDouble(double &value)
{
    std::cin >> value;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

bool Validity::isValidInt(const std::string &input, int &value)
{
    if (input.empty())
        return false;

    int number = 0;
    for (char ch : input)
    {
        if (ch >= '0' && ch <= '9')
        {
            int digit = ch - '0';
            number = number * 10 + digit;
        }
        else
        {
            return false;
        }
    }

    if (number > 0)
    {
        value = number;
        return true;
    }
    return false;
}
