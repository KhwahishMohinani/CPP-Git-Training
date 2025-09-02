#include <iostream>

struct Animal
{
    std::string name;
    int legs;
};

int main()
{
    Animal a;
    Animal *ptr = &a;
    ptr->name = "porcupine";
    ptr->legs = 4;
    std::cout << "name = " << ptr->name << "\n";
    std::cout << "legs = " << ptr->legs << "\n";
    std::cout << "ptr = " << ptr << "\n";
    std::cout << "(*ptr).name = " << (*ptr).name << "\n";
    return 0;
}