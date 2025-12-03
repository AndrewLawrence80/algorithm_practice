#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<int> pipe_a;
    vector<int> pipe_b;
    void init();
    bool solve(vector<int> &nums, int current_idx);
};

int main(int argc, char const *argv[])
{
    int num_cases = 0;
    cin >> num_cases;
    while (num_cases--)
    {
        vector<int> nums(10);
        for (int i = 0; i < 10; i++)
        {
            cin >> nums[i];
        }
        Solution s = Solution();
        s.init();
        if (s.solve(nums, 0))
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    return 0;
}

void Solution::init()
{
    pipe_a = vector<int>(1, 0);
    pipe_b = vector<int>(1, 0);
}

bool Solution::solve(vector<int> &nums, int current_idx)
{
    // 递归基线 1: current_idx 超出 nums.size()，说明所有的球都已放完
    if (current_idx == nums.size())
    {
        return true;
    }

    // 递归基线 2: nums[current_idx] 小于 pipe_a[pipe_a.size() - 1]
    // 且 nums[current_idx] 小于 pipe_b[pipe_b.size() - 1]
    // 说明已经没有候选位置，搜索失败
    if (nums[current_idx] < pipe_a.back() && nums[current_idx] < pipe_b.back())
    {
        return false;
    }

    if (nums[current_idx] > pipe_a.back())
    {
        // 尝试在 pipe_a 放置 nums[current_idx]
        pipe_a.push_back(nums[current_idx]);
        return solve(nums, current_idx + 1);
        pipe_a.pop_back();
    }

    if (nums[current_idx] > pipe_b.back())
    {
        // 尝试在 pipe_b 放置 nums[current_idx]
        pipe_b.push_back(nums[current_idx]);
        return solve(nums, current_idx + 1);
        pipe_b.pop_back();
    }

    return false;
}