#include <cstdio>
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct coordinate{
    int x;
    int y;
};

bool is_valid(coordinate c, int n, int m){
    return 0<=c.x && c.x<n && 0<=c.y && c.y<m;
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

coordinate move_up_left(coordinate c){
    c.x--;
    c.y--;
    return c;
}

coordinate move_up_right(coordinate c){
    c.x++;
    c.y--;
    return c;
}

coordinate move_down_left(coordinate c){
    c.x--;
    c.y++;
    return c;
}

coordinate move_down_right(coordinate c){
    c.x++;
    c.y++;
    return c;
}

int solve(vector<vector<char> > &mat, int n, int m){
    int count = 0;
    deque<coordinate> que;
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            if (mat[i][j] == 'W'){
                count++;
                que.push_back({i, j});
                while (!que.empty()){
                    coordinate cur = que.front();
                    que.pop_front();
                    coordinate left = move_left(cur);
                    coordinate right = move_right(cur);
                    coordinate up = move_up(cur);
                    coordinate down = move_down(cur);
                    coordinate up_left = move_up_left(cur);
                    coordinate up_right = move_up_right(cur);
                    coordinate down_left = move_down_left(cur);
                    coordinate down_right = move_down_right(cur);
                    if (is_valid(left, n, m) && mat[left.x][left.y] == 'W'){
                        mat[left.x][left.y] = '.';
                        que.push_back(left);
                    }
                    if (is_valid(right, n, m) && mat[right.x][right.y] == 'W'){
                        mat[right.x][right.y] = '.';
                        que.push_back(right);
                    }
                    if (is_valid(up, n, m) && mat[up.x][up.y] == 'W'){
                        mat[up.x][up.y] = '.';
                        que.push_back(up);
                    }
                    if (is_valid(down, n, m) && mat[down.x][down.y] == 'W'){
                        mat[down.x][down.y] = '.';
                        que.push_back(down);
                    }
                    if (is_valid(up_left, n, m) && mat[up_left.x][up_left.y] == 'W'){
                        mat[up_left.x][up_left.y] = '.';
                        que.push_back(up_left);
                    }
                    if (is_valid(up_right, n, m) && mat[up_right.x][up_right.y] == 'W'){
                        mat[up_right.x][up_right.y] = '.';
                        que.push_back(up_right);
                    }
                    if (is_valid(down_left, n, m) && mat[down_left.x][down_left.y] == 'W'){
                        mat[down_left.x][down_left.y] = '.';
                        que.push_back(down_left);
                    }
                    if (is_valid(down_right, n, m) && mat[down_right.x][down_right.y] == 'W'){
                        mat[down_right.x][down_right.y] = '.';
                        que.push_back(down_right);
                    }
                }
            }
        }
    }
    return count;
}

int main(int argc, char const *argv[])
{
    int n=0,m=0;
    scanf("%d %d",&n,&m);
    vector<vector<char> > mat(n,vector<char>(m));
    for (int i=0; i<n; i++){
        string s;
        cin >> s;
        for (int j=0; j<m; j++){
            mat[i][j] = s[j] ;
        }
    }
    int result = solve(mat, n, m);
    printf("%d\n", result);
    return 0;
}
