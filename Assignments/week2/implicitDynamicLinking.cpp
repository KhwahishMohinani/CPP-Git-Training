#include <iostream>
#include <cmath>
#include <cfloat>
#include "maths.h"

bool getNumbers(double &num1, double &num2)
{
    std::cout << "Enter two numbers:\n";
    if (!(std::cin >> num1 >> num2))
    {
        std::cerr << "Invalid input\n";
        return false;
    }
    return true;
}

void getChoice(char &mathOperator)
{
    std::cout << "Enter the operator:\n";
    std::cin >> mathOperator;
}

double operation(double num1, double num2, char mathOperator)
{
    double result;
    switch (mathOperator)
    {
    case '+':
        result = addition(num1, num2);
        break;

    case '-':
        result = subtraction(num1, num2);
        break;

    case '*':
        result = multiplication(num1, num2);
        break;

    case '/':
        if (num2 == 0)
        {
            std::cout << "Cannot be divided by zero\n";
            return DBL_MAX;
        }
        result = division(num1, num2);
        break;
    }
    return result;
}

void printResult(double &result)
{
    std::cout << result << "\n";
}

int main()
{
    double num1, num2;
    char mathOperator;
    if (!getNumbers(num1, num2))
        return -1;
    getChoice(mathOperator);
    double result = operation(num1, num2, mathOperator);
    if (result == DBL_MAX)
        return -1;
    printResult(result);
    return 0;
}