#include <iostream>
#include <vector>

/* int main()
{
    int arr[3];

    try
    {
        std::cout << arr[5] << "\n";
        std::cout << "No error\n";
    }
    catch (std::out_of_range)
    {
        std::cout << "Its catched!\n";
    }

    std::cout << "The program is still alive\n";
    return 0;
}

Why doesn’t the catch block trigger?
Because std::out_of_range exceptions are only thrown by safe containers like std::vector::at(), std::string::at(), etc.
Raw arrays and the [] operator do not perform range checking.
*/

int main()
{
    std::vector<int> vec;
    vec.push_back(1);

    try
    {
        std::cout << vec.at(1) << "\n";
        std::cout << "No error\n";
    }
    catch (std::out_of_range) // if we write catch(...) before catch(out of range) the error: handler is masked by default handlerC/C++(532)
    {
        std::cout << "Its catched!\n";
    }
    catch (...) // catch (...) matches any exception type.
    {
        std::cout << "This is all catch block\n";
    }

    std::cout << "The program is still alive\n";
    return 0;
}