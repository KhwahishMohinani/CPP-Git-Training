#ifndef EXPLICIT_DYNAMIC_LINKING
#define EXPLICIT_DYNAMIC_LINKING

struct OperationResult
{
    double value;
    bool errorCode;
};

void getNumbers(double &num1, double &num2);
void getOperator(char &mathOperator);
OperationResult operation(double num1, double num2, char mathOperator);
void printResult(double result);

#endif