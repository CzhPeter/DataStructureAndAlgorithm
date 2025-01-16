/*
将一个８*８的棋盘进行如下分割：将原棋盘割下一块矩形棋盘并使剩下部分也是矩形，再将剩下的部分继续如此分割，
这样割了(n−1)次后，连同最后剩下的矩形棋盘共有 n 块矩形棋盘。(每次切割都只能沿着棋盘格子的边进行)
原棋盘上每一格有一个分值，一块矩形棋盘的总分为其所含各格分值之和。现在需要把棋盘按上述规则分割n
块矩形棋盘，并使各矩形棋盘总分的平方和最小。
​请编程对给出的棋盘及 n，求出平方和的最小值。
输入:
​第1行为一个整数n(1<n<15)。
第2行至第9行每行为8个小于100的非负整数，表示棋盘上相应格子的分值。每行相邻两数之间用一个空格分隔。
输出:
​仅一个数，为最小的平方和值。
输入样例:
3
1 1 1 1 1 1 1 3
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 0
1 1 1 1 1 1 0 3
输出样例:
1460
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

// dp状态: dp[n][i][j][k][l] 表示从(i, j)到(k, l)的矩形，切分 n 块的最小平方和值
// 状态转移方程:
// 枚举棋盘切割位置（分为竖切和横切），在切割位置切下一刀后，分为一块和n - 1块，
// 此时 n 块的最小平方和 = 一块的最小平方和 + n - 1块的最小平方和

int val[10][10] = {0};
int dp[20][10][10][10][10] = {0};

int VAL(int i, int j, int k, int l) {
    return val[k][l] - val[k][j - 1] - val[i - 1][l] + val[i - 1][j - 1];
}

int S(int x) {
    return x * x;
}

#define INF 0x3f3f3f3f

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            scanf("%d", &val[i][j]);
            // val[i][j] 二维前缀和数组 (val[i][j]表示从(0, 0)到(i, j)之间所有元素的和)
            val[i][j] += val[i - 1][j] + val[i][j - 1] - val[i - 1][j - 1];
        }
    }
    // 初始化切割后被分成一块那部分的矩形平方和值
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            for (int k = i; k <= 8; ++k) {
                for (int l = j; l <= 8; ++l) {
                    dp[1][i][j][k][l] = S(VAL(i, j, k, l));
                }
            }
        }
    }
    for (int t = 2; t <= n; ++t) {
        for (int i = 1; i <= 8; ++i) {
            for (int j = 1; j <= 8; ++j) {
                for (int k = i; k <= 8; ++k) {
                    for (int l = j; l <= 8; ++l) {
                        int ans = INF;
                        // 枚举竖切，分别把切割位置左右两部分看成是1块和t-1块的最大平方和，比较取最小值
                        for (int c = j; c < l; ++c) {
                            int val1 = dp[1][i][j][k][c] + dp[t - 1][i][c + 1][k][l];
                            int val2 = dp[t - 1][i][j][k][c] + dp[1][i][c + 1][k][l];
                            ans = min(ans, min(val1, val2));
                        }
                        // 枚举横切，分别把切割位置上下两部分看成是1块和t-1块的最大平方和，比较取最小值
                        for (int c = i; c < k; ++c) {
                            int val1 = dp[1][i][j][c][l] + dp[t - 1][c + 1][j][k][l];
                            int val2 = dp[t - 1][i][j][c][l] + dp[1][c + 1][j][k][l];
                            ans = min(ans, min(val1, val2));
                        }
                        dp[t][i][j][k][l] = ans;
                    }
                }
            }
        }
    }
    printf("%d\n", dp[n][1][1][8][8]);
    return 0;
}

