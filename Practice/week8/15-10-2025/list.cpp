#include <iostream>
#include <list>

void printList(std::list<int> &l)
{
    for (std::list<int>::iterator it = l.begin(); it != l.end(); it++)
    {
        std::cout << *it << "\t";
    }
    std::cout << "\n";
}

int main()
{
    std::list<int> l1 = {1, 2, 3, 4, 5};
    printList(l1);

    std::cout << "size = " << l1.size() << "\n";
    std::cout << "front = " << l1.front() << ", back= " << l1.back() << "\n";
    std::cout << "isEmpty? = " << std::boolalpha << l1.empty() << "\n";

    std::cout << "begin = " << *l1.begin() << ", rbegin = " << *l1.rbegin() << "\n";
    // std::cout << "end = " << *l1.end() << ", rend = " << *l1.rend() << "\n";

    // l1.insert(l1.begin() + 2, 100); //not possible for list, no operator overloading of '+'
    std::list<int>::iterator it = l1.begin();
    while (*it != 3 && it != l1.end())
    {
        it++;
    }
    l1.insert(it, 100);
    printList(l1);
    l1.erase(it);
    printList(l1);
    l1.remove(4);
    printList(l1);

    std::list<int> l2 = l1; // copy
    printList(l2);

    l2.clear();
    printList(l2);
}

/*
l1.end() points one past the last element of the list. It is not dereferenceable. Dereferencing it (*l1.end()) causes undefined behavior — it will likely crash or give garbage.
Similarly, l1.rend() points one before the first element in reverse. Dereferencing it (*l1.rend()) is also undefined.
*/