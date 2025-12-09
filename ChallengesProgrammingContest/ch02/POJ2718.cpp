#include <cstdio>
#include <cstring>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;

int nums[10] = {0};
int n = 0;

void solve()
{
    int result = INT_MAX;

    // 特殊情况：只有2个数字
    if (n == 2)
    {
        result = abs(nums[1] - nums[0]);
        printf("%d\n", result);
        return;
    }
    int median = n / 2;
    do
    {
        int left_sum = 0;
        if (nums[0] == 0 || nums[median] == 0)
        {
            continue;
        }
        for (int i = 0; i < median; i++)
        {
            left_sum = left_sum * 10 + nums[i];
        }
        int right_sum = 0;
        for (int i = median; i < n; i++)
        {
            right_sum = right_sum * 10 + nums[i];
        }
        result = min(result, abs(left_sum - right_sum));
    } while (next_permutation(nums, nums + n));
    printf("%d\n", result);
}

int main(int argc, char const *argv[])
{
    int cases = 0;
    scanf("%d", &cases);

    while (cases--)
    {
        n = 0;
        char ch = 0;
        while (true)
        {
            scanf("%d%c", &nums[n++], &ch);
            if (ch == '\n')
                break;
        }

        sort(nums, nums + n);
        solve();
    }
    return 0;
}