#include <iostream>

int main()
{
    std::string s = "Hello";
    void *ptr = &s;
    // std::cout<<*ptr<<"\n";  //dereferencing is not allowed
    std::string *ptr2 = static_cast<std::string *>(ptr);
    std::cout << *ptr2 << "\n";

    int *ptr3 = static_cast<int *>(ptr); // undefined behaviour
    std::cout << *ptr3 << "\n";          // printing garbage value
}