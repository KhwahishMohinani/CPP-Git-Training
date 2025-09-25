#include <iostream>
#include <fstream>

void reverse(int arr[], int rev_arr[])
{
    for (int i = 0; i < 5; i++)
    {
        rev_arr[i] = arr[5 - i - 1];
    }
}

int main()
{
    int arr[5];
    std::cout << "Enter the numbers: ";
    for (int i = 0; i < 5; i++)
    {
        std::cin >> arr[i];
    }

    std::ofstream fout;
    fout.open("zero.txt");
    fout << "Original array\n";
    for (int i = 0; i < 5; i++)
    {
        fout << arr[i] << " ";
    }

    int rev_arr[5];
    reverse(arr, rev_arr);
    fout << "\nReverse array\n";
    for (int i = 0; i < 5; i++)
    {
        fout << rev_arr[i] << " ";
    }

    fout.close();
}