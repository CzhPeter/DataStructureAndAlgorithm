/*
房间里放着 n 块奶酪。一只小老鼠要把它们都吃掉，问至少要跑多少距离？老鼠一开始在 (0,0) 点处。
输入格式:
第一行有一个整数，表示奶酪的数量 n。
第 2 到第 (n+1) 行，每行两个实数，第 (i+1) 行的实数分别表示第 i 块奶酪的横纵坐标 xi,yi。
输出格式:
输出一行一个实数，表示要跑的最少距离，保留 2 位小数。
样例输入:
4
1 1
1 -1
-1 1
-1 -1
样例输出:
7.41
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define MAX_N 15

int n;
double ans = 1e9;
double x[MAX_N + 5], y[MAX_N + 5];
double dis[MAX_N + 5][MAX_N + 5]; // 表示第i个奶酪到第j个奶酪的距离
double dp[70000][20] = {0}; // dp[i][j]表示在i状态(掩码)下最后一个吃到第j个奶酪时花费的距离
int index_map[70000]; // 掩码和下标的映射关系

#define S(a) ((a) * (a))
double __dis(int i, int j) {
    return sqrt(S(x[i] - x[j]) + S(y[i] - y[j]));
}

// 参数说明:
// t: 当前的掩码状态
// now: 达到当前状态的最后一个点的坐标
// s: 达到当前状态走的总距离
void dfs(int t, int now, double s) {
    if (t == 0) {
        if (s < ans) {
            ans = s; 
            return;
        }
    }
    for (int k = t; k; k -= (k & -k)) {
        int to = index_map[k & -k], next_t = t - (1 << to);
        double l = s + dis[now][to];
        if (dp[next_t][to] != 0 && dp[next_t][to] <= l) {
            continue;
        }
        dp[next_t][to] = l;
        if (ans <= l) {
            continue;
        }
        dfs(next_t, to, l);
    }
    return;
}

int main() {
    scanf("%d", &n);
    x[0] = y[0] = 0;
    double a, b;
    for (int i = 1; i <= n; ++i) {
        scanf("%lf%lf", &a, &b);
        x[i] = a, y[i] = b;
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            dis[i][j] = dis[j][i] = __dis(i, j);
        }
    }
    // 建立掩码状态和下标的映射
    for (int k = 1, i = 0; i <= MAX_N; ++i, k *= 2) {
        index_map[k] = i;
    }
    dfs((1 << (n + 1)) - 2, 0, 0);
    printf("%.2f\n", ans);
    return 0;
}