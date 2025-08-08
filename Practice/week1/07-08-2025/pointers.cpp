#include<iostream>
using namespace std;

int main()
{
    int var = 30;
    int *ptr = &var;

    cout<<"Value of var is: "<<var<<endl;
    cout<<"Address of var is: "<<&var<<endl;
    cout<<"Value of ptr is: "<<ptr<<endl;
    cout<<"Value of *ptr is: "<<*ptr<<endl;

}