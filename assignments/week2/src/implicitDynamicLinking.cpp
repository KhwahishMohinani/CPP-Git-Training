#include <iostream>
#include <cmath>
#include "addition.h"
#include "subtraction.h"
#include "multiplication.h"
#include "division.h"
#include "implicitDynamicLinking.h"

void getNumbers(double &num1, double &num2)
{
    while (true)
    {
        std::cout << "Enter two numbers: ";
        if (std::cin >> num1 >> num2)
        {
            break;
        }
        else
        {
            std::cout << "Invalid input. Please enter valid numbers.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void getOperator(char &mathOperator)
{
    while (true)
    {
        std::cout << "Enter the operator (+, -, *, /) or q to quit: ";
        if (std::cin >> mathOperator)
        {
            if (mathOperator == '+' || mathOperator == '-' || mathOperator == '*' || mathOperator == '/' || mathOperator == 'q' || mathOperator == 'Q')
                return;
        }
        std::cout << "Invalid operator. Try again.\n";
    }
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
            result = {0.0, true};
        }
        else
        {
            result.value = division(num1, num2);
        }
        break;
    default:
        std::cerr << "Invalid operator\n";
        result = {0.0, true};
    }
    return result;
}

void printResult(double result)
{
    std::cout << result << "\n";
}
