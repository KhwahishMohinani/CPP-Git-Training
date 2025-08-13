#include <iostream>
#include <vector>
using namespace std;

void combinationSumRecursion(vector<int> candidates, int target, vector<int> &currentCombination, vector<vector<int>> &result, int index)
{
    if (target == 0)
    {
        result.push_back(currentCombination);
        return;
    }
    if (target < 0 || index == candidates.size())
    {
        return;
    }
    currentCombination.push_back(candidates[index]);
    combinationSumRecursion(candidates, target - candidates[index], currentCombination, result, index);
    currentCombination.pop_back();
    combinationSumRecursion(candidates, target, currentCombination, result, index + 1);
}

vector<vector<int>> combinationSum(vector<int> &candidates, int target)
{
    vector<vector<int>> result;
    vector<int> currentCombination;
    combinationSumRecursion(candidates, target, currentCombination, result, 0);
    return result;
}

int main()
{
    vector<int> candidates;
    int n, target;
    cout << "Enter number of candidates: ";
    cin >> n;

    cout << "Enter candidate numbers: ";
    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;
        candidates.push_back(num);
    }
    cout << "Enter target sum: ";
    cin >> target;

    vector<vector<int>> ans = combinationSum(candidates, target);
    for (auto it : ans)
    {
        for (auto i : it)
        {
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}