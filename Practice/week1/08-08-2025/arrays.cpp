#include<bits/stdc++.h>
using namespace std;

vector<int>two_sum(vector<int>&nums, int target, vector<int>&indexes)
{
    int n = nums.size();
    /*for(int i =0 ; i<n; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            if(nums[i] + nums[j] == target)
            {
                indexes.push_back(i);
                indexes.push_back(j);
                return indexes;
            }
        }
    }*/
    unordered_map<int,int> mpp;
    for(int i =0 ; i<n; i++)
    {
        if(mpp.find(nums[i]) != mpp.end())
        {
            indexes.push_back(i);
            indexes.push_back(mpp[i]);
            return indexes;
        }
        mpp[target - nums[i]] = i;
    }
    return {};
}

int main()
{
    vector<int>nums = {2,7,11,9};
    int target = 9;
    vector<int>indexes;
    two_sum(nums, target, indexes);
    for(auto it: indexes)
    {
        cout<<it<<" ";
    }
    cout<<endl;
    return 0;
}