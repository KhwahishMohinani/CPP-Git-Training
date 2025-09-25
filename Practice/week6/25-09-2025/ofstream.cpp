#include <iostream>
#include <fstream>

int main()
{
    // open the file
    std::ofstream fout;    // fout is an object
    fout.open("zoom.txt"); // if zoom.txt exists, it opens the file. If it doesn't exist, open function creates a file and then calls it
    // write in the file
    fout << "Hello World";

    fout.close(); // to release the resources
}