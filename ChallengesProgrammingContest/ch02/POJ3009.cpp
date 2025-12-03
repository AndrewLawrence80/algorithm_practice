#include <cstdio>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct coordinate
{
    int x, y;
};

class Solution
{
public:
    int solve(vector<vector<int> > &mat, int h, int w, coordinate current, coordinate end, int current_move);
    bool is_reachable(vector<vector<int> > &mat, coordinate current, coordinate end);
    bool is_valid_move(coordinate current, coordinate prev);
    bool is_valid_position(int h, int w, coordinate current, coordinate direction);
    coordinate try_move_left(vector<vector<int> > &mat, coordinate c);
    coordinate try_move_right(vector<vector<int> > &mat, coordinate c);
    coordinate try_move_up(vector<vector<int> > &mat, coordinate c);
    coordinate try_move_down(vector<vector<int> > &mat, coordinate c);
};

int main(int argc, char const *argv[])
{
    int w = 0, h = 0;
    scanf("%d %d", &w, &h);
    while (w > 0 && h > 0)
    {
        vector<vector<int> > mat(h, vector<int>(w));
        coordinate start, end;
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                scanf("%d", &mat[i][j]);
                if (mat[i][j] == 2)
                {
                    start.x = i, start.y = j;
                }
                if (mat[i][j] == 3)
                {
                    end.x = i, end.y = j;
                }
            }
        }
        Solution s = Solution();
        int result = s.solve(mat, h, w, start, end, 0);
        printf("%d\n", result <= 10 ? result : -1);
        scanf("%d %d", &w, &h);
    }
    return 0;
}

bool Solution::is_reachable(vector<vector<int> > &mat, coordinate current, coordinate end)
{
    if (current.x != end.x && current.y != end.y)
    {
        return false;
    }
    // 冰球当前和目的地在同一行或者同一列，且中间无障碍视为可达
    if (current.x == end.x)
    {
        int start_y = min(current.y, end.y);
        int end_y = max(current.y, end.y);
        for (int i = start_y + 1; i < end_y; i++)
        {
            if (mat[current.x][i] == 1)
            {
                return false;
            }
        }
        return true;
    }
    if (current.y == end.y)
    {
        int start_x = min(current.x, end.x);
        int end_x = max(current.x, end.x);
        for (int i = start_x + 1; i < end_x; i++)
        {
            if (mat[i][current.y] == 1)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Solution::is_valid_move(coordinate current, coordinate prev)
{
    return current.x != prev.x || current.y != prev.y;
}

bool Solution::is_valid_position(int h, int w, coordinate current, coordinate direction)
{
    // 冰球移到边界就是出局了
    if (direction.y == -1 && direction.x == 0)
    {
        return current.y > 0 && current.y < w - 1;
    }
    if (direction.y == 1 && direction.x == 0)
    {
        return current.y > 0 && current.y < w - 1;
    }
    if (direction.x == -1 && direction.y == 0)
    {
        return current.x > 0 && current.x < h - 1;
    }
    if (direction.x == 1 && direction.y == 0)
    {
        return current.x > 0 && current.x < h - 1;
    }
    return false;
}

coordinate Solution::try_move_left(vector<vector<int> > &mat, coordinate c)
{
    while (c.y)
    {
        if (c.y >= 1 && mat[c.x][c.y - 1] == 1)
        {
            // 再往左一步就是障碍物
            break;
        }
        c.y--;
    }
    return c;
}

coordinate Solution::try_move_right(vector<vector<int> > &mat, coordinate c)
{
    while (c.y < mat[0].size() - 1)
    {
        if (c.y <= mat[0].size() - 2 && mat[c.x][c.y + 1] == 1)
        {
            // 再往右一步就是障碍物
            break;
        }
        c.y++;
    }
    return c;
}

coordinate Solution::try_move_up(vector<vector<int> > &mat, coordinate c)
{
    while (c.x)
    {
        if (c.x >= 1 && mat[c.x - 1][c.y] == 1)
        {
            // 再往上一步就是障碍物
            break;
        }
        c.x--;
    }
    return c;
}

coordinate Solution::try_move_down(vector<vector<int> > &mat, coordinate c)
{
    while (c.x < mat.size() - 1)
    {
        if (c.x <= mat.size() - 2 && mat[c.x + 1][c.y] == 1)
        {
            // 再往下一步就是障碍物
            break;
        }
        c.x++;
    }
    return c;
}

int Solution::solve(vector<vector<int> > &mat, int h, int w, coordinate current, coordinate end, int current_move)
{
    // 基线: 再走一步就是目的地
    if (is_reachable(mat, current, end))
    {
        return current_move + 1;
    }

    int min_result = INT_MAX;
    // 寻找所有可能的移动
    coordinate possible_left = try_move_left(mat, current);
    if (is_valid_move(possible_left, current) && is_valid_position(h, w, possible_left, {0, -1}))

    {
        mat[possible_left.x][possible_left.y - 1] = 0; // 移除障碍物
        int result = solve(mat, h, w, possible_left, end, current_move + 1);
        if (result != -1)
        {
            min_result = min(min_result, result);
        }
        mat[possible_left.x][possible_left.y - 1] = 1; // 恢复障碍物
    }
    coordinate possible_right = try_move_right(mat, current);
    if (is_valid_move(possible_right, current) && is_valid_position(h, w, possible_right, {0, 1}))
    {
        mat[possible_right.x][possible_right.y + 1] = 0; // 移除障碍物
        int result = solve(mat, h, w, possible_right, end, current_move + 1);
        if (result != -1)
        {
            min_result = min(min_result, result);
        }
        mat[possible_right.x][possible_right.y + 1] = 1; // 恢复障碍物
    }
    coordinate possible_up = try_move_up(mat, current);
    if (is_valid_move(possible_up, current) && is_valid_position(h, w, possible_up, {-1, 0}))
    {
        mat[possible_up.x - 1][possible_up.y] = 0; // 移除障碍物
        int result = solve(mat, h, w, possible_up, end, current_move + 1);
        if (result != -1)
        {
            min_result = min(min_result, result);
        }
        mat[possible_up.x - 1][possible_up.y] = 1; // 恢复障碍物
    }
    coordinate possible_down = try_move_down(mat, current);
    if (is_valid_move(possible_down, current) && is_valid_position(h, w, possible_down, {1, 0}))
    {
        mat[possible_down.x + 1][possible_down.y] = 0; // 移除障碍物
        int result = solve(mat, h, w, possible_down, end, current_move + 1);
        if (result != -1)
        {
            min_result = min(min_result, result);
        }
        mat[possible_down.x + 1][possible_down.y] = 1; // 恢复障碍物
    }
    if (min_result == INT_MAX) // 未找到可行解
    {
        return -1;
    }
    else
    {
        return min_result;
    }
    return -1;
}