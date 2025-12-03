#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

struct coordinate
{
    int x, y;
};

bool is_valid(int h, int w, coordinate &c)
{
    return 0 <= c.x && c.x < h && 0 <= c.y && c.y < w;
}

coordinate move_left(coordinate c){
    c.x--;
    return c;
}

coordinate move_right(coordinate c){
    c.x++;
    return c;
}

coordinate move_up(coordinate c){
    c.y--;
    return c;
}

coordinate move_down(coordinate c){
    c.y++;
    return c;
}

void solve(vector<vector<char> > &mat, int h, int w, coordinate start);

int main(int argc, char const *argv[])
{
    int h = 0, w = 0;
    cin >> w >> h;
    while (h != 0 && w != 0)
    {
        vector<vector <char> > mat(h, vector<char>(w));
        int x = -1, y = -1;
        for (int i = 0; i < h; i++)
        {
            string s;
            cin >> s;
            vector<char> row(s.begin(), s.end());
            mat[i] = row;
            int y_pos = s.find('@');
            if (y_pos != string::npos)
            {
                x = i;
                y = y_pos;
            }
        }
        solve(mat, h, w, {x,y});
        cin >> w >> h;
    }
    return 0;
}

void solve(vector<vector<char> > &mat, int h, int w, coordinate start)
{
    int count = 0;
    deque<coordinate> que;
    que.push_back(start);
    while (!que.empty())
    {
        count++;
        coordinate current = que.front();
        que.pop_front();
        coordinate left = move_left(current);
        coordinate right = move_right(current);
        coordinate up = move_up(current);
        coordinate down = move_down(current);
        if (is_valid(h, w, left) && mat[left.x][left.y] == '.'){
            mat[left.x][left.y] = '#';
            que.push_back(left);
        }
        if (is_valid(h, w, right) && mat[right.x][right.y] == '.'){
            mat[right.x][right.y] = '#';
            que.push_back(right);
        }
        if (is_valid(h, w, up) && mat[up.x][up.y] == '.'){
            mat[up.x][up.y] = '#';
            que.push_back(up);
        }
        if (is_valid(h, w, down) && mat[down.x][down.y] == '.'){
            mat[down.x][down.y] = '#';
            que.push_back(down);
        }
    }
    printf("%d\n", count);
}