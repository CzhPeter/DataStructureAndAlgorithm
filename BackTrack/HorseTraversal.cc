/*
有一个 n×m 的棋盘，在某个点 (x,y) 上有一个马，要求你计算出马到达棋盘上任意一个点最少要走几步。
马的走法参照中国象棋，走日。
输入格式: 
输入只有一行四个整数，分别为 n,m,x,y。
输出格式: 
一个 n×m 的矩阵，代表马到达某个点最少要走几步（不能到达则输出 −1）。
样例输入:
3 3 1 1
样例输出: 
0    3    2    
3    -1   1    
2    1    4
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAX_N 400
// 方向数组，8个方向，每个方向2个便宜量，表示马的所有移动方式
int direct[8][2] = {
    {2, 1}, {-2, 1}, {2, -1}, {-2, -1},
    {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
};
int dis[MAX_N + 5][MAX_N + 5]; // dis[i][j]代表起点到(i, j)点的最短距离
int n, m;

struct Node {
    Node(int x, int y, int s) : x(x), y(y), s(s) {}
    int x, y, s; // 到达(x, y)的最短距离是s步
};

// 参数说明: 
// n, m: 棋盘大小
// x, y: 当前点的坐标
void bfs(int n, int m, int x, int y) {
    queue<Node> q;
    q.push(Node(x, y, 0));
    dis[x][y] = 0;
    while (!q.empty()) {
        Node now = q.front();
        q.pop();
        for (int k = 0; k < 8; ++k) {
            int dx = now.x + direct[k][0];
            int dy = now.y + direct[k][1];
            if (dx < 1 || dx > n) continue;
            if (dy < 1 || dy > m) continue;
            if (dis[dx][dy] != -1) continue;
            q.push(Node(dx, dy, now.s + 1));
            dis[dx][dy] = now.s + 1;
        }
    }
    return;
}

// 参数说明: 
// step: 起点到达当前(x, y)点的总步数
// x, y: 当前点的坐标
void dfs(int step, int x, int y) {
    if (dis[x][y] != -1 && dis[x][y] <= step) {
        return;
    }
    dis[x][y] = step;
    for (int k = 0; k < 8; ++k) {
        int dx = x + direct[k][0];
        int dy = y + direct[k][1];
        if (dx < 1 || dx > n) continue;
        if (dy < 1 || dy > m) continue;
        dfs(step + 1, dx, dy);
    }
    return;
}

int main() {
    int x, y;
    cin >> n >> m >> x >> y;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dis[i][j] = -1;
        }
    }
    // dfs(0, x, y);
    bfs(n, m, x, y);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (j > 1) cout << " ";
            cout << dis[i][j];
        }
        cout << endl;
    }
    return 0;
}