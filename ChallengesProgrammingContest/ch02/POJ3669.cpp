#include <cstdio>
#include <vector>
#include <deque>
#include <climits>

using namespace std;

// 地图时间稍微大一点
const int MAX_N = 500;
const int MAX_T = 1500;

struct coordinate
{
    int x, y, step;
};

coordinate move(coordinate current, coordinate direction)
{
    return {current.x + direction.x, current.y + direction.y};
}

class Solution
{
public:
    vector<vector<int>> step_mat;
    int solve(vector<vector<int>> &mat, vector<vector<coordinate>> meteors, int max_t);
    void strike(vector<vector<int>> &mat, vector<vector<coordinate>> meteors, int max_t);
    bool is_valid(coordinate &c);
    vector<coordinate> bfs(vector<vector<int>> &mat, coordinate start, int current_t);
};

int main(int argc, char const *argv[])
{
    vector<vector<coordinate>> meteors(MAX_T);
    int m = 0;
    scanf("%d", &m);
    int max_time = 0;
    for (int i = 0; i < m; i++)
    {
        int x = 0, y = 0, t = 0;
        scanf("%d %d %d", &x, &y, &t);
        max_time = max(max_time, t);
        meteors[t].push_back({x, y});
    }
    vector<vector<int>> mat(MAX_N, vector<int>(MAX_N, INT_MAX));
    Solution s;
    printf("%d\n", s.solve(mat, meteors, max_time));
    return 0;
}

bool Solution::is_valid(coordinate &c)
{
    return c.x >= 0 && c.y >= 0;
}

int Solution::solve(vector<vector<int>> &mat, vector<vector<coordinate>> meteors, int max_t)
{
    strike(mat, meteors, max_t);

    // 检查起点是否在时间 0 就被摧毁
    if (mat[0][0] == 0)
    {
        return -1;
    }

    // 如果起点永远不会被摧毁，直接返回 0
    if (mat[0][0] == INT_MAX)
    {
        return 0;
    }

    deque<coordinate> que;
    vector<vector<bool>> visited(MAX_N, vector<bool>(MAX_N, false));
    que.push_back({0, 0, 0});
    visited[0][0] = true; // 标记起点为已访问

    coordinate directions[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    while (!que.empty())
    {
        coordinate current = que.front();
        que.pop_front();

        // 尝试向四个方向移动
        for (int i = 0; i < 4; i++)
        {
            coordinate next = move(current, directions[i]);
            next.step = current.step + 1;

            // 检查是否是有效位置且未访问过
            if (!is_valid(next) || visited[next.x][next.y])
            {
                continue;
            }

            // 检查在到达时间 next.step 时，该位置是否安全
            if (mat[next.x][next.y] > next.step)
            {
                // 如果该位置永远不会被摧毁，找到了安全位置
                if (mat[next.x][next.y] == INT_MAX)
                {
                    return next.step;
                }

                visited[next.x][next.y] = true;
                que.push_back(next);
            }
        }
    }

    return -1; // 找不到安全位置
}

void Solution::strike(vector<vector<int>> &mat, vector<vector<coordinate>> meteors, int max_t)
{
    coordinate directions[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (int t = 0; t <= max_t; t++)
    {
        for (int i = 0; i < meteors[t].size(); i++)
        {
            coordinate meteor = meteors[t][i];
            // 在 t 时刻该点被砸中，记录最早被砸中的时间
            mat[meteor.x][meteor.y] = min(mat[meteor.x][meteor.y], t);
            for (int j = 0; j < 4; j++)
            {
                // 顺便让周围的点也被砸中
                coordinate next = move(meteor, directions[j]);
                if (is_valid(next))
                {
                    mat[next.x][next.y] = min(mat[next.x][next.y], t);
                }
            }
        }
    }
}