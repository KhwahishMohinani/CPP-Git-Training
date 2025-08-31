#include <iostream>

struct matrix
{
    int **data;
    int rows;
    int columns;
};

void getDimensions(int &rows, int &columns)
{
    std::cout << "Enter the number of rows: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns: ";
    std::cin >> columns;
}

matrix createMatrix(int rows, int columns)
{
    matrix m;
    m.rows = rows;
    m.columns = columns;
    m.data = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        m.data[i] = new int[columns];
    }
    return m;
}

void getValues(matrix &m)
{
    std::cout << "Enter the values of the matrix\n";
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.columns; j++)
        {
            std::cin >> m.data[i][j];
        }
    }
}

void printValues(const matrix &m)
{
    std::cout << "Matrix:\n";
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.columns; j++)
        {
            std::cout << m.data[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

matrix prepareMatrix()
{
    int rows, columns;
    getDimensions(rows, columns);
    matrix m = createMatrix(rows, columns);
    getValues(m);
    printValues(m);
    return m;
}

void getOperator(char &opr)
{
    while (true)
    {
        std::cout << "Enter the Operation\n";
        std::cout << "For Addition, enter '+'\n";
        std::cout << "For Multiplication, enter '*'\n";
        std::cin >> opr;

        if (opr == '+' || opr == '*')
        {
            return;
        }
        else
        {
            std::cout << "Invalid operator. Please try again.\n";
        }
    }
}

bool isValidForAddition(const matrix &m1, const matrix &m2)
{
    if (m1.rows == m2.rows && m1.columns == m2.columns)
        return true;
    return false;
}

bool isValidForMultiplication(const matrix &m1, const matrix &m2)
{
    if (m1.columns == m2.rows)
        return true;
    return false;
}

matrix performAddition(const matrix &m1, const matrix &m2)
{
    matrix resultMatrix = createMatrix(m1.rows, m1.columns);
    for (int i = 0; i < m1.rows; i++)
    {
        for (int j = 0; j < m1.columns; j++)
        {
            resultMatrix.data[i][j] = m1.data[i][j] + m2.data[i][j];
        }
    }
    return resultMatrix;
}

matrix performMultiplication(const matrix &m1, const matrix &m2)
{
    matrix resultMatrix = createMatrix(m1.rows, m2.columns);
    for (int i = 0; i < m1.rows; i++)
    {
        for (int j = 0; j < m2.columns; j++)
        {
            resultMatrix.data[i][j] = 0;
            for (int k = 0; k < m1.columns; k++)
            {
                resultMatrix.data[i][j] += m1.data[i][k] * m2.data[k][j];
            }
        }
    }
    return resultMatrix;
}

matrix executeOperation(char opr, const matrix &m1, const matrix &m2)
{
    matrix resultMatrix = {nullptr, 0, 0};
    switch (opr)
    {
    case '+':
    {
        if (!isValidForAddition(m1, m2))
        {
            std::cout << "Cannot perform addition\n";
        }
        else
        {
            resultMatrix = performAddition(m1, m2);
        }
        break;
    }
    case '*':
    {
        if (!isValidForMultiplication(m1, m2))
        {
            std::cout << "Cannot perform multiplication\n";
        }
        else
        {
            resultMatrix = performMultiplication(m1, m2);
        }
        break;
    }
    default:
    {
        std::cout << "Invalid Operator\n";
        break;
    }
    }
    return resultMatrix;
}

void deleteMatrix(matrix &m)
{
    for (int i = 0; i < m.rows; i++)
    {
        delete[] m.data[i];
    }
    delete[] m.data;
    m.data = nullptr;
    m.rows = 0;
    m.columns = 0;
}

int main()
{
    char opr;
    matrix m1 = prepareMatrix();
    std::cout << "For second matrix\n";
    matrix m2 = prepareMatrix();
    getOperator(opr);
    matrix resultMatrix = executeOperation(opr, m1, m2);

    if (resultMatrix.data != nullptr)
    {
        printValues(resultMatrix);
        deleteMatrix(resultMatrix);
    }

    deleteMatrix(m1);
    deleteMatrix(m2);
    return 0;
}