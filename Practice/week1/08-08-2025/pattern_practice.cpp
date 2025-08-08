#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n = 7;
    for(int i = 0; i<n; i++)
    {
        for(int j=0; j<=i; j++)
        {
            if(j%2 == 0) cout<<"1 ";
            else cout<<"0 ";
        }
        for(int j=i; j<n-1; j++)
        {
            cout<<"  ";
        }
        for(int j=i+1; j<n-1;j++)
        {
            cout<<"  ";
        }
        for(int j=0; j<=i; j++)
        {
            
            if(j%2 == 0) 
            {
                if(i==n-1 && j == 0)
                {
                    continue;
                }
                else{
                cout<<"1 ";
                }
            }
            else cout<<"0 ";
        }
        cout<<endl;
    }
    for(int i = 0; i<n-1; i++)
    {
        for(int j =0; j<n-1-i; j++)
        {
            if(j%2 == 0) cout<<"1 ";
            else cout<<"0 ";
        }
        for(int j=0; j<=i; j++)
        {
            cout<<"  ";
        }
        for(int j=1; j<=i; j++)
        {
            cout<<"  ";
        }
        for(int j =0; j<n-1-i; j++)
        {
            if(j%2 == 0) cout<<"1 ";
            else cout<<"0 ";
        }
        cout<<endl;
    }
}