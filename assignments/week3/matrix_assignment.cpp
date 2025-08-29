#include <iostream>

void getDimensions(int &rows, int &columns)
{
    std::cout << "Enter the number of rows: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns: ";
    std::cin >> columns;
}

int **createMatrix(int rows, int columns)
{
    int **matrix = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new int[columns];
    }
    return matrix;
}

void getValues(int **matrix, int rows, int columns)
{
    std::cout << "Enter the values of the matrix\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            std::cin >> matrix[i][j];
        }
    }
}

void printValues(int **matrix, int rows, int columns)
{
    std::cout << "Matrix:\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

void getOperator(char &opr)
{
    std::cout << "Enter the Operation\n";
    std::cout << "For Addition, enter '+'\n";
    std::cout << "For Multiplication, enter '*'\n";
    std::cin >> opr;
}

bool isValidForAddition(int rows1, int columns1, int rows2, int columns2)
{
    if (rows1 == rows2 && columns1 == columns2)
        return true;
    return false;
}

bool isValidForMultiplication(int columns1, int rows2)
{
    if (columns1 == rows2)
        return true;
    return false;
}

int **performAddition(int **matrix1, int **matrix2, int rows, int columns)
{
    int **resultMatrix = createMatrix(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            resultMatrix[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return resultMatrix;
}

int **performMultiplication(int **matrix1, int **matrix2, int rows1, int columns1, int columns2)
{
    int **resultMatrix = createMatrix(rows1, columns2);
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < columns2; j++)
        {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < columns1; k++)
            {
                resultMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return resultMatrix;
}

void deleteMatrix(int **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main()
{
    int rows1, columns1, rows2, columns2;
    char opr;
    getDimensions(rows1, columns1);
    int **matrix1 = createMatrix(rows1, columns1);
    getValues(matrix1, rows1, columns1);
    printValues(matrix1, rows1, columns1);
    std::cout << "For second matrix\n";
    getDimensions(rows2, columns2);
    int **matrix2 = createMatrix(rows2, columns2);
    getValues(matrix2, rows2, columns2);
    printValues(matrix2, rows2, columns2);
    getOperator(opr);
    int **resultMatrix;
    switch (opr)
    {
    case '+':
    {
        if (!isValidForAddition(rows1, columns1, rows2, columns2))
        {
            std::cout << "Cannot perform addition\n";
            deleteMatrix(matrix2, rows2);
            deleteMatrix(matrix1, rows1);
            return 1;
        }
        resultMatrix = performAddition(matrix1, matrix2, rows1, columns1);
        printValues(resultMatrix, rows1, columns1);
        deleteMatrix(resultMatrix, rows1);
        break;
    }
    case '*':
    {
        if (!isValidForMultiplication(columns1, rows2))
        {
            std::cout << "Cannot perform multiplication\n";
            deleteMatrix(matrix2, rows2);
            deleteMatrix(matrix1, rows1);
            return 1;
        }
        resultMatrix = performMultiplication(matrix1, matrix2, rows1, columns1, columns2);
        printValues(resultMatrix, rows1, columns2);
        deleteMatrix(resultMatrix, rows1);
        break;
    }
    default:
    {
        std::cout << "Invalid Operator\n";
        break;
    }
    }
    deleteMatrix(matrix2, rows2);
    deleteMatrix(matrix1, rows1);
    return 0;
}