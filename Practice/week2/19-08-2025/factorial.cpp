int factorial(int num)
{
    if (num == 0 || num == 1)
        return num;
    int result = 1;
    for (int i = 2; i <= num; i++)
    {
        result = result * i;
    }
    return result;
}