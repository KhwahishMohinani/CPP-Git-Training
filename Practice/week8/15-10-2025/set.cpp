#include <iostream>
#include <set>

struct Person
{
    int age;
    std::string name;

    bool operator<(const Person &other) const
    {
        return age < other.age;
    }
    /*The std::set internally uses the < operator to compare elements as const references, because it never modifies the elements.
    So, your comparator must be const and take a const reference.*/
};

void printSet(std::set<int> &s)
{
    for (std::set<int>::iterator it = s.begin(); it != s.end(); it++)
    {
        std::cout << *it << "\t";
    }
    std::cout << "\n";
}

void printSet(const std::set<int, std::greater<int>> &s)
{
    for (auto it = s.begin(); it != s.end(); ++it)
    {
        std::cout << *it << "\t";
    }
    std::cout << "\n";
}

int main()
{
    std::set<int> s;
    s.insert(10);
    s.insert(20);
    s.insert(110);
    s.insert(220);
    s.insert(110);
    s.insert(120);
    s.insert(20);
    s.insert(30);

    printSet(s);

    if (s.find(220) != s.end())
        std::cout << "Present\n";
    else
        std::cout << "Absent\n";

    std::cout << "Count of 20: " << s.count(20) << "\n";

    s.erase(110);
    std::cout << "Count of 100: " << s.count(110) << "\n";

    // std::set<int, std::greater<int>> s2 = s;
    // std::set<int> is actually std::set<int, std::less<int>>
    // std::set<int, std::greater<int>> is a different type

    std::set<int, std::greater<int>> s2 = {6, 1, 4, 2, 9, 6, 4, 5, 8}; // descending order
    printSet(s2);

    std::set<Person> personSet;
    Person p1, p2;
    p1.age = 12, p1.name = "Jennie";
    p2.age = 19, p2.name = "Jisoo";

    personSet.insert(p1);
    personSet.insert(p2);

    for (std::set<Person>::iterator it = personSet.begin(); it != personSet.end(); it++)
    {
        std::cout << "age = " << (*it).age << ", name = " << (*it).name << "\n"; // can also use it->
    }
}