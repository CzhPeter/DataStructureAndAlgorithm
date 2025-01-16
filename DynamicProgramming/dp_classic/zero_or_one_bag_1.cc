/*
给一个能承重V的背包，和n件物品，我们用重量和价值的二元组来表示一个物品，
第i件物品表示为（Vi，Wi），问：在背包不超重的情况下，得到物品的最大价值是多少？
输入:
第一行输入两个数 V,n，分别代表背包的最大承重和物品数。
接下来n行，每行两个数Vi,Wi，分别代表第i件物品的重量和价值。
(Vi≤V≤10000,n≤100,Wi≤1000000)
输出:
输出一个整数，代表在背包不超重情况下所装物品的最大价值。
样例输入1
15 4
4 10
3 7
12 12
9 8
样例输出1
19
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// dp状态: dp[i][j] 表示前i件物品，背包承重为j时所获得的最大价值
// 状态转移方程:
// 不选第i件物品: dp[i][j] = dp[i - 1][j] 相当于选i - 1件物品，重量为j的价值最大值 
// 选第i件物品: dp[i][j] = dp[i - 1][j - v[i]] + w[i] 相当于选i - 1件物品，重量为j - v[i]的价值最大值， 加上第i件物品的价值
// dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - v[i]] + w[i])

#define MAX_N 100
#define MAX_V 10000
int v[MAX_N + 5], w[MAX_N + 5];
int dp[2][MAX_V + 5]; // 滚动数组，因为dp[i][j]只与dp[i - 1][j]有关系

int main() {
    int V, n;
    cin >> V >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> v[i] >> w[i];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= V; ++j) {
            int index = i % 2, pre_index = (i - 1) % 2;
            dp[index][j] = dp[pre_index][j];
            if (j < v[i]) continue; // 当前的背包容量放不下第 i 件物品
            dp[index][j] = max(dp[index][j], dp[pre_index][j - v[i]] + w[i]);
        }
    }
    cout << dp[n % 2][V] << endl;
    return 0;
}
