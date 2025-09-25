#include <iostream>
#include <fstream>

int main()
{
    std::ofstream fout;
    fout.open("lines.txt");
    fout << "Hello World\n";
    fout << "I am learning C++\n";
    fout << "This is file handling\n";
    fout.close();

    std::ifstream fin;
    fin.open("lines.txt");

    std::string line;

    while (getline(fin, line))
    {
        std::cout << line << "\n";
    }

    fin.close();
}

// get function is used to get the data with space