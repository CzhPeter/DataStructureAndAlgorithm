/*
有 N 种物品和一个容量为 V 的背包，每种物品都有无限件可用。
第 i 种物品的体积是 Ci ，价值是 Wi 。求解在不超过背包容量的情况下，能够获得的最大价值。
输入:
第一行为两个整数 N、V(1≤N,V≤10000)，分别代表题目描述中的物品种类数量 N 和背包容量 V 。
后跟N行，第 i 行两个整数 Ci、Vi ，分别代表每种物品的体积和价值。
输出:
输出一个整数，代表可获得的最大价值。
样例输入:
5 20
2 3
3 4
10 9
5 2
11 11
样例输出:
30
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// dp状态: dp[i][j] 表示前i件物品，背包承重为j时所获得的最大价值
// 状态转移方程:
// 不选第 i 件物品: dp[i][j] = dp[i - 1][j]
// 选第 i 件物品: dp[i][j - v[i]] + w[i] 因为物品是无限的，这个式子相当于留出了一个第 i 件物品的空间，剩下的还是在 i 种物品中选
// dp[i][j] = max(dp[i - 1][j], dp[i][j - v[i]] + w[i])

#define MAX_V 10000
int dp[MAX_V + 5];

int main() {
    int n, V;
    cin >> n >> V;
    for (int i = 1, c, v; i <= n; ++i) {
        cin >> c >> v;
        for (int j = c; j <= V; ++j) { // 正序遍历，确保dp[j - c]的状态先更新
            dp[j] = max(dp[j], dp[j - c] + v);
        }
    }
    cout << dp[V] << endl;
    return 0;
}