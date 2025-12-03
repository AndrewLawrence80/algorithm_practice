#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

void solve(vector<int> &nums);

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
        solve(nums);
    }
    return 0;
}

void solve(vector<int> &nums)
{
    int left_max = 0, right_max = 0;
    bool result = true;
    for (int i = 0; result && i < nums.size(); i++)
    {
        int x = nums[i];
        int distance_to_left = x - left_max;
        int distance_to_right = x - right_max;
        if (max(distance_to_left, distance_to_right) < 0)
        {
            result = false;
            continue;
        }
        if (distance_to_left >= 0 && distance_to_right < 0)
        {
            left_max = x;
        }
        if (distance_to_left < 0 && distance_to_right >= 0)
        {
            right_max = x;
        }
        if (distance_to_left > 0 && distance_to_right > 0)
        {
            if (distance_to_left < distance_to_right)
            {
                left_max = x;
            }
            else
            {
                right_max = x;
            }
        }
    }
    if (result)
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
}