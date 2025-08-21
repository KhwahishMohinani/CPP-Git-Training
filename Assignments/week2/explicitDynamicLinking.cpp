#include <iostream>
#include <cmath>
#include <cfloat>
#include <dlfcn.h>

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
    void *handle = dlopen("./libmaths.so", RTLD_LAZY);
    if (!handle)
    {
        std::cerr << "Cannot load file " << dlerror() << "\n";
        return DBL_MAX;
    }

    double result = DBL_MAX;
    switch (mathOperator)
    {
    case '+':
    {
        typedef double (*addition_t)(double, double);
        addition_t addition = (addition_t)dlsym(handle, "addition");

        const char *error = dlerror();
        if (error != NULL)
        {
            std::cerr << "Cannot load symbol addition " << error << "\n";
            dlclose(handle);
            return DBL_MAX;
        }
        result = addition(num1, num2);
        break;
    }
    case '-':
    {
        typedef double (*subtraction_t)(double, double);
        subtraction_t subtraction = (subtraction_t)dlsym(handle, "subtraction");

        const char *error = dlerror();
        if (error != NULL)
        {
            std::cerr << "Cannot load symbol subtraction " << error << "\n";
            dlclose(handle);
            return DBL_MAX;
        }
        result = subtraction(num1, num2);
        break;
    }
    case '*':
    {
        typedef double (*multiplication_t)(double, double);
        multiplication_t multiplication = (multiplication_t)dlsym(handle, "multiplication");

        const char *error = dlerror();
        if (error != NULL)
        {
            std::cerr << "Cannot load symbol multiplication " << error << "\n";
            dlclose(handle);
            return DBL_MAX;
        }
        result = multiplication(num1, num2);
        break;
    }
    case '/':
    {
        if (num2 == 0)
        {
            std::cout << "Cannot be divided by zero\n";
            dlclose(handle);
            return DBL_MAX;
        }

        typedef double (*division_t)(double, double);
        division_t division = (division_t)dlsym(handle, "division");

        const char *error = dlerror();
        if (error != NULL)
        {
            std::cerr << "Cannot load symbol division " << error << "\n";
            dlclose(handle);
            return DBL_MAX;
        }
        result = division(num1, num2);
        break;
    }
    default:
        std::cerr << "Invalid operator\n";
        dlclose(handle);
        return DBL_MAX;
    }
    dlclose(handle);
    return result;
}

void printResult(double &result)
{
    if (result != INFINITY && result != -INFINITY)
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