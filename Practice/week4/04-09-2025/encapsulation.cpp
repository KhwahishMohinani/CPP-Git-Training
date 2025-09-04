#include <iostream>

/*struct Employee
{
    std::string name = "John";
    char firstInitial = name.front();

    void print() const
    {
        std::cout << "Employee " << name << " has the first initial " << firstInitial << "\n";
    }
};

int main()
{
    Employee e1;
    e1.print();
    Employee e2;
    e2.name = "Mark";
    e2.print();
}*/

class Employee
{
    std::string name = "John";
    char firstInitial = 'J';

public:
    void setValue(std::string name)
    {
        this->name = name;
        firstInitial = name.front();
    }

    void print() const
    {
        std::cout << "Employee " << name << " has the first initial " << firstInitial << "\n";
    }
};

int main()
{
    Employee e1;
    e1.print();
    Employee e2;
    e2.setValue("Mark");
    e2.print();
}
