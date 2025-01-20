/*
给有一个能承重 V 的背包，和n种物品，每种物品的数量有限多，我们用重量、价值和数量的三元组来表示一个物品，
第 i 件物品表示为（Vi，Wi，Si），问在背包不超重的情况下，得到物品的最大价值是多少？
输入:
第一行输入两个数V、n，分别代表背包的最大承重和物品种类数。
接下来 n 行，每行三个数 Vi、Wi、Si，分别代表第 i 种物品的重量、价值和数量。
输出:
输出一个整数，代表在背包不超重情况下所装物品的最大价值。
样例输入:
15 4
4 10 5
3 7 4
12 12 2
9 8 7
样例输出:
37
*/

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// dp状态: dp[i][j] 代表前 i 件物品，背包承重为 j 时所获得的最大价值
// 假设当前物品重量为5，价值为6，数量为3
// dp[i][7] 取0件当前物品: dp[i - 1][7]，取1件当前物品: dp[i - 1][2] + 6
// dp[i][12] 取0件当前物品: dp[i - 1][12]，取1件当前物品: dp[i - 1][7] + 6，取2件当前物品: dp[i - 1][2] + 12
// 可以得出规律，dp[i][j] 中的 j 对于某一物品的多组解，其 j (重量)值是同余的，余数即当前物品的重量
// 因此可以分组求解进行优化
// 同时，dp[i][7] 减去偏移量 6，dp[i][12] 减去偏移量 12，...，就可以得到一系列相同的项，比如 dp[i - 1][7] - 6
// 此时，就可以对这些项设置一个滑动窗口逐渐扩大，
// 每组取滑动窗口中的最大值，再加上偏移量，就是每个组的最大价值，该工作可以通过单调队列来完成

#define MAX_V 100000
#define MAX_N 100
int dp[MAX_N + 5][MAX_V + 5] = {0};

int main() {
    int V, n;
    cin >> V >> n;
    for (int i = 1, v, w, s; i <= n; ++i) {
        cin >> v >> w >> s;
        // 枚举重量，用余数系分组
        for (int r = 0; r < v; ++r) {
            deque<int> q;
            for (int j = r; j <= V; j += v) {
                dp[i - 1][j] -= j / v * w;
                // 维护单调队列
                while (!q.empty() && dp[i - 1][q.back()] < dp[i - 1][j]) {
                    q.pop_back();
                }
                q.push_back(j);
                // 物品数量超出上限就弹出队列头
                if ((j - q.front()) / v > s) q.pop_front();
                dp[i][j] = dp[i - 1][q.front()] + j / v * w;
            }
        }
    }
    cout << dp[n][V] << endl;
    return 0;
}