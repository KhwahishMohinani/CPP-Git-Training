#include <iostream>
int main()
{
    int *p = new int(5);
    int *q = new int(6);
    p = q;
    delete (p);
    delete (q);
    return 0;
}