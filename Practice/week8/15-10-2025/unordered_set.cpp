#include <iostream>
#include <unordered_set>

void printUnorderedSet(const std::unordered_set<int> &s)
{
    for (auto it = s.begin(); it != s.end(); ++it)
    {
        std::cout << *it << "\t";
    }
    std::cout << "\n";
}

int main()
{
    std::unordered_set<int> s;
    s.insert(10);
    s.insert(20);
    s.insert(110);
    s.insert(220);
    s.insert(110);
    s.insert(120);
    s.insert(20);
    s.insert(30);

    printUnorderedSet(s);
}