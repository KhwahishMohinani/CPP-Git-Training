#include <algorithm>
#include <iostream>

class Foo
{
private:
    int m_x{};
    int m_y{};

public:
    Foo(int x, int y)
        : m_y{std::max(x, y)}, m_x{m_y} // Even though m_y is listed first in the member initialization list, because m_x is defined first in the class, m_x gets initialized first. And m_x gets initialized to the value of m_y, which hasn’t been initialized yet. Finally, m_y gets initialized to the greater of the initialization values.
    {
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo{6, 7};
    foo.print();

    return 0;
}