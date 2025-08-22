#include <iostream>
#include <cmath>
#include <cfloat>
#include "maths.h"

struct OperationResult
{
    double value;
    bool errorCode;
};

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

OperationResult operation(double num1, double num2, char mathOperator)
{
    OperationResult result = {0.0, false};
    switch (mathOperator)
    {
    case '+':
        result.value = addition(num1, num2);
        break;

    case '-':
        result.value = subtraction(num1, num2);
        break;

    case '*':
        result.value = multiplication(num1, num2);
        break;

    case '/':
        if (num2 == 0)
        {
            std::cerr << "Cannot be divided by zero\n";
            return {0.0, true};
        }
        result.value = division(num1, num2);
        break;
    default:
        std::cerr << "Invalid operator\n";
        return {0.0, true};
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
    OperationResult ans = operation(num1, num2, mathOperator);
    if (ans.errorCode == true)
    {
        std::cerr << "Operation Failed\n";
        return -1;
    }
    printResult(ans.value);
    return 0;
}