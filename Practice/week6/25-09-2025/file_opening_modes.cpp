#include <iostream>
#include <fstream>

int main()
{
    std::ofstream fout;
    fout.open("example.txt", std::ios::binary);
    fout << "Hello, this is written in binary mode!\n";
    fout.close();
}