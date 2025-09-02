#include <iostream>

struct cat
{
    std::string name = "cat";
    int legs = 4;
};

struct dog
{
    std::string name = "dog";
    int legs = 4;
};

struct snake
{
    std::string name = "snake";
    int legs = 0;
};

int main()
{
    snake animal;
    std::cout << "A " << animal.name << " has " << animal.legs << " legs\n";
    return 0;
}