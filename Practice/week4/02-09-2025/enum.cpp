#include <iostream>

enum AnimalType
{
    cat,
    dog,
    rabbit,
    snake
};

std::string AnimalName(AnimalType type)
{
    switch (type)
    {
    case cat:
        return "cat";
    case dog:
        return "dog";
    case rabbit:
        return "rabbit";
    case snake:
        return "snake";
    }
}

int AnimalLegs(AnimalType type)
{
    switch (type)
    {
    case cat:
        return 4;
    case dog:
        return 4;
    case rabbit:
        return 2;
    case snake:
        return 0;
    }
}

int main()
{
    AnimalType animal{snake};
    std::cout << "A " << AnimalName(animal) << " has " << AnimalLegs(animal) << " legs\n";
    return 0;
}