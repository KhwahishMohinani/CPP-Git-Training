#include <iostream>

class Data
{
public:
    void printData(Data &data)
    {
        std::cout << getData();
    }

    std::string getData()
    {
        return "Hello";
    }
};

int main()
{
    Data data;
    data.printData(data);
}