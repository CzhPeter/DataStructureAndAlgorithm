/*
图上有一个矩阵，由 N×M 个格子组成，这些格子由两种颜色构成，黑色和白色。
请找到面积最大的且内部是黑白交错（即两个相连的正方形颜色不能相同）的正方形。
输入格式:
第一行两个整数 N 和 M，分别表示行数和列数。
接下来有 N 行，每行 M 个数，0 或 1 分别表示这个格子是黑色或白色。
输出格式:
仅有一行，表示满足条件最大正方形的边长。
样例输入:
3 3
0 1 0
1 0 0
1 1 1
样例输出:
2
*/

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

// dp状态: dp[i][j] 代表以 (i, j) 为右下角的最大正方形的边长
// 状态转移: 
// dp[i][j] <= dp[i - 1][j - 1] + 1
// 设 (i, j) 点向上数的黑白相间格子数量为 a，向左数的黑白格子数量为 b
// dp[i][j] = min(dp[i - 1][j - 1] + 1, a, b)

#define MAX_N 1500
int dp[MAX_N + 5][MAX_N + 5][2]; // 最后一维表示 (i, j) 点为 0 或 1 时候的最大正方形面积

int main() {
    int n, m, ans = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1, a; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &a);
            dp[i][j][1 - a] = 0;
            dp[i][j][a] = min(dp[i - 1][j - 1][a], 
                              min(dp[i - 1][j][1 - a], dp[i][j - 1][1 - a])) + 1;
            ans = max(ans, dp[i][j][a]);
        }
    }
    cout << ans << endl;
    return 0;
}