#include <iostream>
#include <limits>
#include <dlfcn.h>
#include "explicitDynamicLinking.h"

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
    void *handle = dlopen("./build/libmaths.so", RTLD_LAZY);
    if (!handle)
    {
        std::cerr << "Cannot load file " << dlerror() << "\n";
        result = {0.0, true};
    }
    else
    {
        switch (mathOperator)
        {
        case '+':
        {
            double (*addition)(double, double) = (double (*)(double, double))dlsym(handle, "addition");
            const char *error = dlerror();
            if (error != NULL)
            {
                std::cerr << "Cannot load symbol addition " << error << "\n";
                result = {0.0, true};
            }
            else
            {
                result.value = addition(num1, num2);
            }
            break;
        }
        case '-':
        {
            double (*subtraction)(double, double) = (double (*)(double, double))dlsym(handle, "subtraction");

            const char *error = dlerror();
            if (error != NULL)
            {
                std::cerr << "Cannot load symbol subtraction " << error << "\n";
                result = {0.0, true};
            }
            else
            {
                result.value = subtraction(num1, num2);
            }
            break;
        }
        case '*':
        {
            double (*multiplication)(double, double) = (double (*)(double, double))dlsym(handle, "multiplication");

            const char *error = dlerror();
            if (error != NULL)
            {
                std::cerr << "Cannot load symbol multiplication " << error << "\n";
                result = {0.0, true};
            }
            else
            {
                result.value = multiplication(num1, num2);
            }
            break;
        }
        case '/':
        {
            if (num2 == 0)
            {
                std::cout << "Cannot be divided by zero\n";
                result = {0.0, true};
            }
            else
            {
                double (*division)(double, double) = (double (*)(double, double))dlsym(handle, "division");

                const char *error = dlerror();
                if (error != NULL)
                {
                    std::cerr << "Cannot load symbol division " << error << "\n";
                    result = {0.0, true};
                }
                else
                {
                    result.value = division(num1, num2);
                }
            }
            break;
        }
        default:
            std::cerr << "Invalid operator\n";
            result = {0.0, true};
        }
        dlclose(handle);
    }
    return result;
}

void printResult(double result)
{
    std::cout << result << "\n";
}
