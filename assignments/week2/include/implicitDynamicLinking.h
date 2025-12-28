#ifndef IMPLICIT_DYNAMIC_LINKING_H
#define IMPLICIT_DYNAMIC_LINKING_H

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