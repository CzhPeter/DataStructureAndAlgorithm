/*
定义鸡蛋的硬度为 k，则代表鸡蛋最高从 k 楼扔下来不会碎掉，
现在给你 n 个硬度相同的鸡蛋，楼高为 m，问最坏情况下最少测多少次，可以测出鸡蛋的硬度
输入:
输入两个数字 n,m（1≤n≤32,1≤m<231），代表 n 个鸡蛋和 m 层楼。
输出:
输出一行整数，代表最坏情况下最少测多少次可以测出鸡蛋的硬度。
样例输入:
2 100
样例输出:
14
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

// dp状态重定义思路:
// dp[i][j] = k，楼层越高，扔次数越多，即 j 与 k 正相关，同时 j 范围大，k 范围小，可以将 j 和 k 互换:
// dp[i][k] = j 表示 i 个鸡蛋扔 k 次，最多可以测多少层楼
// 状态转移方程: dp[i][k] = dp[i][k - 1] + dp[i - 1][k - 1] + 1
// 此时 k 的求解方式: 当 dp[n][k - 1] < m <= dp[n][k] 时，k 为正解

#define MAX_N 32
#define MAX_K 1000
long long dp[MAX_N + 5][MAX_K + 5];

int main() {
    long long n, m;
    cin >> n >> m;
    if (n == 1) {
        cout << m << endl;
        return 0;
    }
    for (int i = 1; i <= MAX_K; ++i) {
        dp[1][i] = i; // 初始化: 一个鸡蛋扔 i 次最多测 i 层楼
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= MAX_K; ++j) {
            dp[i][j] = dp[i][j - 1] + dp[i - 1][j - 1] + 1;
            if (dp[i][j] > m) {
                break;
            }
        }
    }
    int k = 1;
    while (dp[n][k] < m) {
        k += 1;
    }
    cout << k << endl;
    return 0;
}