#include <iostream>
#include <fstream>

int main()
{
    std::ifstream in("file.txt");
    std::string oldData;
    getline(in, oldData);
    std::cout << "Old data: " << oldData << "\n";

    std::ofstream out("file.txt");
    out << "New content";

    in.open("file.txt");
    std::string newData;
    getline(in, newData);
    std::cout << "Read again: " << newData << "\n";
}
