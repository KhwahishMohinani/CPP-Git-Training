#include <iostream>

class Person
{
    std::string name;
    int age;

    Person(std::string input_name, int input_age)
        : name(input_name), age(input_age)
    {
        std::cout << "Constructor called\n";
    }

public:
    void showData()
    {
        std::cout << "Name: " << name << "\n";
        std::cout << "Age: " << age << "\n";
    }
    friend Person take_input(std::string input_name, int input_age);
};

Person take_input(std::string input_name, int input_age)
{
    // Validation condition can be put here
    return Person(input_name, input_age);
}

int main()
{
    std::string name;
    int age;
    std::cout << "Please enter name: ";
    std::cin >> name;
    std::cout << "Please enter age: ";
    std::cin >> age;
    Person p = take_input(name, age);
    // Person p1(name,age);  // would not work
    p.showData();
}