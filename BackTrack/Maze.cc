/*
给定一个 N×M 方格的迷宫，迷宫里有 T 处障碍，障碍处不可通过。
在迷宫中移动有上下左右四种方式，每次只能移动一个方格。数据保证起点上没有障碍。
给定起点坐标和终点坐标，每个方格最多经过一次，问有多少种从起点坐标到终点坐标的方案。
输入格式: 
第一行为三个正整数 N,M,T，分别表示迷宫的长宽和障碍总数。
第二行为四个正整数 SX,SY,FX,FY，SX,SY 代表起点坐标，FX,FY 代表终点坐标。
接下来 T 行，每行两个正整数，表示障碍点的坐标。
输出格式: 
输出从起点坐标到终点坐标的方案总数。
样例输入:
2 2 1
1 1 2 2
1 2
样例输出:
1
*/

#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 5
int direct[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int g[MAX_N + 5][MAX_N + 5]; // g[i][j] = 1代表该坐标可以走，0代表该坐标不可走
int n, m, t, x_1, x_2, y_1, y_2, ans;

// 参数说明: x, y: 当前点的坐标
void dfs(int x, int y) {
    if (x == x_2 && y == y_2) {
        ans += 1;
        return;
    }
    g[x][y] = 0;
    for (int i = 0; i < 4; ++i) {
        int dx = x + direct[i][0];
        int dy = y + direct[i][1];
        if (g[dx][dy] == 0) continue;
        dfs(dx, dy);
    }
    g[x][y] = 1;
    return;
}

int main() {
    cin >> n >> m >> t;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            g[i][j] = 1;
        }
    }
    cin >> x_1 >> y_1 >> x_2 >> y_2;
    for (int i = 0, x, y; i < t; ++i) {
        cin >> x >> y;
        g[x][y] = 0;
    }
    ans = 0;
    dfs(x_1, y_1);
    cout << ans << endl;
    return 0;
}