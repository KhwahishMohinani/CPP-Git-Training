#include<bits/stdc++.h>
using namespace std; 

int main()
{
    int n = 4;
    /*1*/
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<=i; j++)
        {
            cout<<"*";
        }
        cout<<endl;
    }
    cout << endl;
    /*2*/
    for(int i=0; i<n; i++)
    {
        for(int j=i; j<n; j++)
        {
            cout<<"*";
        }
        cout<<endl;
    }
    cout << endl;
    /*3*/
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<=i; j++)
        {
            cout<<" ";
        }
        for(int j = i; j<n; j++)
        {
            cout<<"*";
        }
        cout<<endl;
    }
    cout << endl;
    /*4*/
    for(int i = 0; i<n; i++)
    {
        for(int j = i; j<n; j++)
        {
            cout<<" ";
        }
        for(int j = 0; j<=i; j++)
        {
            cout<<"*";
        }
        cout<<endl;
    }
    cout<<endl;
    /*5*/
    for(int i = 0; i<n; i++)
    {
        for(int j=0; j<=i; j++)
        {
            cout<<"*";
        }
        for(int j=i; j<n-1; j++)
        {
            cout<<" ";
        }
        for(int j=i; j<n-1;j++)
        {
            cout<<" ";
        }
        for(int j=0; j<=i; j++)
        {
            cout<<"*";
        }
        cout<<endl;
    }
    for(int i = 0; i<n-1; i++)
    {
        for(int j=i; j<n-1; j++)
        {
            cout<<"*";
        }
        for(int j =0; j<=i; j++)
        {
            cout<<" ";
        }
        for(int j =0; j<=i; j++)
        {
            cout<<" ";
        }
        for(int j=i; j<n-1; j++)
        {
            cout<<"*";
        }
        cout<<endl;
    }
    return 0;
}