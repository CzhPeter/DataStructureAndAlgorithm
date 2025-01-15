/*
https://www.luogu.com.cn/problem/P1038
输入格式:
输入文件第一行是两个整数 n（1≤n≤100）和 p。
接下来 n 行，每行 2 个整数，第 i+1 行是神经元 i 最初状态和其阈值（Ui），非输入层的神经元开始时状态必然为 0。
再下面 p 行，每行有两个整数 i,j 及一个整数 Wij ，表示连接神经元 i,j 的边权值为 Wij。
输出格式:
输出文件包含若干行，每行有 2 个整数，分别对应一个神经元的编号，及其最后的状态，
2 个整数间以空格分隔。仅输出最后状态大于 0 的输出层神经元状态，并且按照编号由小到大顺序输出。
若输出层的神经元最后状态均小于等于 0，则输出 NULL。
样例输入:
5 6
1 0
1 0
0 1
0 1
0 1
1 3 1
1 4 1
1 5 1
2 3 1
2 4 1
2 5 1
样例输出:
3 1
4 1
5 1
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

// 用拓扑序计算每个神经元的值，将 Ci > 0 的节点加入拓扑序队列，出度 = 0 的节点为输出层

#define MAX_N 100
int C[MAX_N + 5]; // 记录每个节点的状态
int U[MAX_N + 5]; // 记录每个节点的阈值
int W[MAX_N + 5][MAX_N + 5]; // 记录由i到j边的权值
int in_degree[MAX_N + 5], out_degree[MAX_N + 5]; // 记录每个节点的出度
vector<int> g[MAX_N + 5]; // 记录每个节点指向的节点

int main() {
    int n, p;
    cin >> n >> p;
    for (int i = 1; i <= n; ++i) {
        cin >> C[i] >> U[i];
        if (C[i] == 0) {
            C[i] = -U[i];
        }
    }
    for (int i = 0, a, b, w; i < p; ++i) {
        cin >> a >> b >> w;
        W[a][b] = w;
        in_degree[b] += 1;
        out_degree[a] += 1;
        g[a].push_back(b);
    }
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] != 0) continue;
        q.push(i);
    }
    while (!q.empty()) {
        int index = q.front();
        q.pop();
        if (C[index] > 0) {
            for (int i = 0; i < g[index].size(); ++i) {
                int to = g[index][i];
                C[to] += W[index][to] * C[index];
            }
        }
        for (int i = 0; i < g[index].size(); ++i) {
            int to = g[index][i];
            in_degree[to] -= 1;
            if (in_degree[to] == 0) {
                q.push(to);
            }
        }
    }
    int flag = 0;
    for (int i = 1; i <= n; ++i) {
        if (out_degree[i] != 0) continue;
        if (C[i] <= 0) continue;
        cout << i << " " << C[i] << endl;
        flag = 1;
    }
    if (flag == 0) cout << "NULL" << endl;
    return 0;
}