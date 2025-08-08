#include<bits/stdc++.h>
using namespace std;

int minimum_path_sum(int i, int j, vector<vector<int>>nums)
{
    if(i == 0 && j==0) 
    {
        return nums[i][j];
    }
    int up = INT_MAX,left = INT_MAX;
    if(i>0) up = nums[i][j] + minimum_path_sum(i-1,j, nums);
    if(j>0) left = nums[i][j] + minimum_path_sum(i,j-1, nums);
    return min(up , left);
}

int main()
{
    vector<vector<int>> nums = {{1,3,1},{1,5,1},{4,2,1}};
    int path_sum = minimum_path_sum(2,2, nums);
    cout<<path_sum<<endl;
    return 0;
}