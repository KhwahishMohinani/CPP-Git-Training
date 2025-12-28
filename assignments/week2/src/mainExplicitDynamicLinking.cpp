#include <iostream>
#include "explicitDynamicLinking.h"

int main()
{
    double num1, num2;
    char mathOperator;
    getNumbers(num1, num2);
    while (true)
    {
        getOperator(mathOperator);
        if (mathOperator == 'q' || mathOperator == 'Q')
            break;
        OperationResult ans = operation(num1, num2, mathOperator);
        if (ans.errorCode == true)
        {
            std::cerr << "Operation failed!\n";
            return -1;
        }
        printResult(ans.value);
    }
    return 0;
}