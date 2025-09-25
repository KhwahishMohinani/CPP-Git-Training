#include <iostream>
#include <fstream>

int main()
{
    std::ifstream fin;
    fin.open("zoom.txt");
    char c;
    // fin >> c; //doesn't treat space as a character
    c = fin.get();
    while (!fin.eof())
    {
        std::cout << c;
        // fin >> c;
        c = fin.get();
    }

    fin.close();
}