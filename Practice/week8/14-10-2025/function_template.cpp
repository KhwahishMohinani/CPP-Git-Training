#include <iostream>

template <typename X, typename Y> // instead of 'typename', we can also write 'class'
X greater(X a, Y b)               // function template or generic function
{
    if (a > b)
        return a;
    return b;
}

int main()
{
    std::cout << greater(2, 5) << "\n";
    std::cout << greater(8.9, 3.4) << "\n";
    std::cout << greater("s", "a") << "\n";
    // std::cout << greater("g", 8) << "\n";
}