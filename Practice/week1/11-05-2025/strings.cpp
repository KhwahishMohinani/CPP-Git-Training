#include<iostream>
#include<string>
using namespace std;

bool isPalindrome(string s, int start, int end)
{
    while(end>start)
    {
        if(s[start] != s[end]) 
            return false;
        start++;
        end--;
    }
    return true;
}

string longest_palindromic_substring(string s)
{
    int n = s.length();
    string lps;
    int max_len = 1;
    if(n==0 || n==1) return s;
    for(int i=0; i<n; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            if(isPalindrome(s,i,j) && j-i+1 > max_len)
            {
                max_len = j-i;
                lps = s.substr(i, j-i+1);
            }
        }
    }
    return lps;
}

int main()
{
    string s = "cbababsas";
    string lps = longest_palindromic_substring(s);
    cout<<lps;
    return 0;
}