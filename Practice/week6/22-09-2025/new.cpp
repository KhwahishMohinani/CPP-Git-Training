#include <iostream>
#include <string>

class Student
{
    std::string name;
    int age;

public:
    Student(const std::string &n, int a) : name(n), age(a) {}

    void printDetails()
    {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }

    void incrementAge()
    {
        age++;
    }

    int getAge()
    {
        return age;
    }
};

int main()
{
    Student s("Alice", 20);

    s.printDetails();

    for (int i = 0; i < 5; i++)
    {
        s.incrementAge();
    }

    if (s.getAge() == 25)
    {
        std::cout << "Student is 25 years old.\n";
    }

    s.printDetails();

    return 0;
}
