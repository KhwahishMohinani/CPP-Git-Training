#include<iostream>
using namespace std;

int main()
{
    try
    {
        int *p = new int[10000000000000000];
        cout<<"Memory allocation is succesfully done";
    }
    catch(const exception& e)
    {
        cout<<"Exception occurred due to line 8"<<e.what()<<endl;
    }
    
}