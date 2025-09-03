#include <iostream>

class Animal
{
public:
    void print(Animal &animal)
    {
        std::cout << name << " eats " << animal.name << "\n";
    }

    std::string name{another_name};
    std::string another_name{"jaanvar"}; // declaration order doesn't matter but definition order matters for variables not functions
    std::string color{};
    int weight{};
    int legs{};
};

void print(Animal &animal)
{
    std::cout << animal.name << " does not eat " << animal.name << "\n";
}

int main()
{
    Animal snake{"snake", "viper", "green", 5, 4};
    Animal rabbit{"rabbit", "bunny", "white", 5, 4};
    snake.print(rabbit);
    print(snake);
    std::cout << snake.another_name << " 1 " << snake.name << "\n";
    std::cout << rabbit.another_name << " 2 " << rabbit.name << "\n";
    Animal tiger;
    tiger.print(snake);
}