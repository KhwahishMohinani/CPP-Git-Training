#include <iostream>
#include <fstream>

int main()
{
    std::ofstream out("file.txt");
    out << "New content";

    std::ofstream out2("file.txt");
    out2 << "Extremely New content";

    out.close();
    out2.close();

    std::ifstream in("file.txt");
    std::string content;
    getline(in, content);
    std::cout << "Read data: " << content << "\n";
}
