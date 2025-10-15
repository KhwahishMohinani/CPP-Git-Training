#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = {1, 2, 3};
    std::cout << "size = " << v.size() << "\n";
    std::cout << "capacity = " << v.capacity() << "\n";
    std::cout << "max size = " << v.max_size() << "\n";
    v.push_back(5);
    std::cout << "size = " << v.size() << "\n";
    std::cout << "capacity = " << v.capacity() << "\n";
    std::cout << "max size = " << v.max_size() << "\n";
    int cap = v.capacity();
    for (int i = 0; i < 100; i++)
    {
        v.push_back(8);
        if (cap != v.capacity())
        {
            std::cout << "capacity = " << v.capacity() << "\n";
            cap = v.capacity();
        }
    }
    std::cout << "v.at(103) = " << v.at(103) << "\n";
    std::cout << "v[103] = " << v[103] << "\n";

    // std::cout << "v.at(104) = " << v.at(104) << "\n"; // while accessing out of bound memory it is terminating
    // std::cout << "v[104]" << v[104] << "\n";          // while accessing out of bound memory it is printing 0

    std::cout << "front = " << v.front() << "\n";
    std::cout << "back = " << v.back() << "\n";

    // std::cout << "v.begin() = " << v.begin() << "\n";  // won't work looks like a pointer but is not
    std::cout << "*v.begin() = " << *v.begin() << "\n";
    v.insert(v.begin() + 2, -100);
    std::cout << v[2] << "\n";
    std::cout << "size = " << v.size() << "\n";
    std::cout << "capacity = " << v.capacity() << "\n";
    v.pop_back();
    std::cout << "size = " << v.size() << "\n";
    std::cout << "capacity = " << v.capacity() << "\n";
    std::cout << "v[5] = " << v[5] << "\n";
    v.erase(v.begin() + 5); // All elements after index 5 are shifted left by one. So the element that was at v[6] now becomes v[5], v[7] becomes v[6]
    std::cout << "v[5] = " << v[5] << "\n";
}