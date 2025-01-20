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

// 思路: 共 n 颗鸡蛋 m 层楼，第一颗鸡蛋在第 k 层楼往下扔，
// 如果没碎，就用 n 个鸡蛋测 m - k 层楼的情况；如果碎了，就用 n - 1 颗鸡蛋测 k - 1 层楼的情况
// dp状态: dp[i][j] 代表前 i 个鸡蛋测 j 层楼的最坏最少次数
// 状态转移方程: dp[i][j] = min(max(dp[i][j - k], dp[i - 1][k - 1])) + 1

#define MAX_N 32
#define MAX_M 100000
int dp[MAX_N][MAX_M];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        dp[1][i] = i; // 一个鸡蛋最坏情况就是测 m 层楼次
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <=m; ++j) {
            dp[i][j] = j; 
            for (int k = 1; k <= j; ++k) {
                dp[i][j] = min(dp[i][j], max(dp[i - 1][k - 1], dp[i][j - k]) + 1);
            }
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}