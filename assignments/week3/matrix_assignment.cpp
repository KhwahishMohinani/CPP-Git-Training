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

void getOperator(char &opr)
{
    std::cout << "Enter the Operation\n";
    std::cout << "For Addition, enter '+'\n";
    std::cout << "For Multiplication, enter '*'\n";
    std::cin >> opr;
}

bool areSameSize(int **matrix1, int **matrix2)
{
}

int **performOperation(int **matrix1, int **matrix2, char opr)
{
    switch (opr)
    {
    case '+':
        areSameSize(matrix1, matrix2);
    }
}

int main()
{
    int rows1, columns1, rows2, columns2;
    char opr;
    getDimensions(rows1, columns1);
    int **matrix1 = createMatrix(rows1, columns1);
    std::cout << "For second matrix\n";
    getDimensions(rows2, columns2);
    int **matrix2 = createMatrix(rows2, columns2);
    getOperator(opr);
    performOperation(matrix1, matrix2, opr);
    return 0;
}