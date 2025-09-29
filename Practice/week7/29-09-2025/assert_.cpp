#include <assert.h>

int addNumbers(int a, int b)
{
    return a + b;
}

int subtractNumbers(int a, int b)
{
    return a - b;
}

void test_add()
{
    assert(addNumbers(3, 5) == 8);
    assert(addNumbers(5, 7) == 9); // Internally call abort if condition fails
}

void test_subtract()
{
    assert(subtractNumbers(9, 0) == 3);
    assert(subtractNumbers(5, 7) == 9);
}

int main()
{
    test_add();
    test_subtract();
    return 0;
}