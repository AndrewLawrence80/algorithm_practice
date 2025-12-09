#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> nums = {1, 2, 3};
    while (next_permutation(nums.begin(), nums.end()))
    {
        for (int num : nums)
            cout << num << " ";
        cout << endl;
    }
    return 0;
}
