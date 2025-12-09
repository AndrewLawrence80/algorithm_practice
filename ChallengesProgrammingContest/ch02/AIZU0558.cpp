#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct coordinate
{
    int x, y, step;
};

coordinate move(coordinate current, coordinate direction)
{
    return {current.x + direction.x, current.y + direction.y};
}

bool operator==(const coordinate &a, const coordinate &b)
{
    return a.x == b.x && a.y == b.y;
}

bool is_valid(int h, int w, coordinate c)
{
    return 0 <= c.x && c.x < h && 0 <= c.y && c.y < w;
}

class Solution
{
public:
    int solve(vector<vector<char>> &mat, int h, int w, vector<coordinate> &cheeses);
    int bfs(vector<vector<char>> mat, int h, int w, coordinate start, coordinate end);
};

int main(int argc, char const *argv[])
{
    int h = 0, w = 0, n = 0;
    cin >> h >> w >> n;
    vector<vector<char>> mat(h, vector<char>(w));
    vector<coordinate> cheeses(n + 1);
    for (int i = 0; i < h; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < w; j++)
        {
            mat[i][j] = s[j];
            if (mat[i][j] == 'S')
            {
                cheeses[0] = {i, j};
            }
            if (mat[i][j] >= '1' && mat[i][j] <= '0' + n)
            {
                cheeses[mat[i][j] - '0'] = {i, j};
            }
        }
    }
    Solution s;
    cout << s.solve(mat, h, w, cheeses) << endl;
    return 0;
}

int Solution::solve(vector<vector<char>> &mat, int h, int w, vector<coordinate> &cheeses)
{
    int total_step = 0;
    for (int i = 1; i <= cheeses.size() - 1; i++)
    {
        total_step += bfs(mat, h, w, cheeses[i - 1], cheeses[i]);
    }
    return total_step;
}

// 注意这里 mat 需要使用复制传参，防止 BFS 设置走过的地方已经不能走的逻辑在求解前后两轮最短路径的时候互相影响
int Solution::bfs(vector<vector<char>> mat, int h, int w, coordinate start, coordinate end)
{
    coordinate direction[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    deque<coordinate> que;
    start.step = 0;
    que.push_back(start);
    while (!que.empty())
    {
        coordinate current = que.front();
        que.pop_front();
        if (current == end)
        {
            return current.step;
        }
        for (int i = 0; i < 4; i++)
        {
            coordinate next = move(current, direction[i]);
            if (is_valid(h, w, next) && mat[next.x][next.y] != 'X')
            {
                mat[next.x][next.y] = 'X'; // 防止 BFS 回头，也是导致复制传参 mat 的关键
                next.step = current.step + 1;
                que.push_back(next);
            }
        }
    }
    return -1; // 根据题意这个逻辑不可能被执行到
}