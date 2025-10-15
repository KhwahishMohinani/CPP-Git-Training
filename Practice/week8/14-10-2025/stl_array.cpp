#include <iostream>
#include <array>

int main()
{
    std::array<int, 7> data_array = {11, 22, 33, 44, 55};
    std::cout << data_array.at(2) << "\n";
    std::cout << data_array[2] << "\n";
    std::cout << data_array.back() << "\n";

    data_array.fill(10);
    for (int i = 0; i < 7; i++)
    {
        std::cout << data_array[i] << "\t";
    }
    std::cout << "\n";

    std::array<int, 5> data_array2 = {11, 22, 33, 44, 55};
    std::array<int, 5> data_array3 = {1, 2, 3, 4, 5};
    data_array2.swap(data_array3);
    for (int i = 0; i < 5; i++)
    {
        std::cout << data_array2[i] << "\t";
    }
    std::cout << "\n";
    for (int i = 0; i < 5; i++)
    {
        std::cout << data_array3[i] << "\t";
    }
    std::cout << "\n";

    std::cout << data_array3.size() << "\n";
}