#include <iostream>
#include <map>

void printMap(std::map<int, int> &m)
{
    for (std::map<int, int>::iterator it = m.begin(); it != m.end(); it++)
    {
        std::cout << it->first << " = " << it->second << "\n";
    }
}

void printMultiMap(std::multimap<int, int> &m)
{
    for (std::multimap<int, int>::iterator it = m.begin(); it != m.end(); it++)
    {
        std::cout << it->first << " = " << it->second << "\n";
    }
}

int main()
{
    std::map<int, int> m;
    m.insert(std::make_pair(12, 30));
    m.insert(std::make_pair(14, 39));
    m.insert(std::make_pair(12, 30));
    m.insert(std::make_pair(12, 10)); // no updation
    m.insert(std::make_pair(19, 30));
    m[20] = 6; // update is allowed
    printMap(m);

    std::cout << "Count of 20: " << m.count(20) << "\n";
    std::cout << "Count of 12: " << m.count(12) << "\n";

    m.erase(14);
    printMap(m);
    std::cout << "\n";
    std::cout << "Multimap:\n";
    std::multimap<int, int> mm;
    mm.insert(std::make_pair(12, 30));
    mm.insert(std::make_pair(14, 39));
    mm.insert(std::make_pair(12, 30));
    mm.insert(std::make_pair(12, 10));
    mm.insert(std::make_pair(19, 30));
    // mm[20] = 6; //not allowed
    printMultiMap(mm);
}
