#include <iostream>

template <typename T>
class Box
{
    int capacity;
    T *arr_ptr;

public:
    Box(int size) : capacity(size)
    {
        arr_ptr = new T[capacity];
    }
    void addElement(int index, T data)
    {
        if (index >= 0 && index < capacity)
        {
            arr_ptr[index] = data;
        }
        else
            std::cout << "Invalid Index\n";
    }
    void viewElement(int index)
    {
        if (index >= 0 && index < capacity)
        {
            std::cout << arr_ptr[index] << "\n";
        }
        else
            std::cout << "Invalid Index\n";
    }
    void viewList()
    {
        for (int i = 0; i < capacity; i++)
        {
            std::cout << arr_ptr[i] << "\t";
        }
        std::cout << "\n";
    }
    ~Box()
    {
        delete[] arr_ptr;
    }
};

int main()
{
    // Box box(4); //the constructor takes int size, not a T, so the compiler can’t deduce T from that.
    Box<int> box(4);
    box.addElement(0, 4);
    box.addElement(1, 9);
    box.addElement(2, 5);
    box.addElement(3, 3);
    box.viewElement(2);
    box.viewList();
}