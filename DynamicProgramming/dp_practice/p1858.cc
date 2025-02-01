/*
求01背包前k优解的价值和
DD 和好朋友们要去爬山啦！
他们一共有 K 个人，每个人都会背一个包。这些包 的容量是相同的，都是 V。
可以装进背包里的一共有 N 种物品，每种物品都有 给定的体积和价值。
在 DD 看来，合理的背包安排方案是这样的： 每个人背包里装的物品的总体积恰等于包的容量。 
每个包里的每种物品最多只有一件，但两个不同的包中可以存在相同的物品。
任意两个人，他们包里的物品清单不能完全相同。 
在满足以上要求的前提下，所有包里的所有物品的总价值最大是多少呢？
输入格式:
第一行三个数K、V、N
接下来每行两个数，表示体积和价值
输出格式:
前k优解的价值和
样例输入:
2 10 5
3 12
7 20
2 4
5 6
1 1
样例输出:
57
*/

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

// dp状态: 假设 dp[i][j] 存储着第 i 个物品在 j 容量下最优物品组合的前 k 优个解
// 状态转移: 
// 按 0/1 背包: dp = max(dp[i - 1][j], dp[i - 1][j - v[i]] + w[i])
// 其中 dp[i - 1][j] 和 dp[i - 1][j - v[i]] 也各有其前 k 优个解，共 2k 个
// 那么 dp[i][j] 的前 k 优个解，一定是从这 2k 个解中得到的，采用归并排序的方式来筛选解

#define MAX_V 5000
#define MAX_K 50
int dp[MAX_V + 5][MAX_K + 5]; // dp[j][k] 表示容量为 j 的背包的 第 k 优解 的价值
int temp[MAX_K + 5];

int main() {
    int K, V, N;
    cin >> K >> V >> N;
    // dp[j][0] 表示容量为 j 的背包的 解的个数
    dp[0][0] = 1; // 容量为 0 的背包只有一种解
    // dp[j][1] 到 dp[j][k] 表示容量为 j 的背包的 前 k 优解 的价值
    dp[0][1] = 0; // 容量为 0 的背包唯一解价值为 0
    for (int i = 0, v, w; i < N; ++i) {
        cin >> v >> w;
        for (int j = V; j >= v; --j) {
            int p1 = 1, p2 = 1, t = 1; // p1 和 p2 分别指向 dp[j] 和 dp[j - v] 的起始位置，用于比较两者价值
            int n1 = dp[j][0], n2 = dp[j - v][0]; // n1 和 n2 分别表示 dp[j] 和 dp[j - v] 的解的个数
            // 使用归并排序的思想，从 dp[j] 和 dp[j - v] + w 中选出前 k 优解，存入 temp
            while (p1 <= n1 || p2 <= n2) {
                if (p2 > n2 || (p1 <= n1 && dp[j][p1] >= dp[j - v][p2] + w)) {
                    temp[t++] = dp[j][p1++];
                } else {
                    temp[t++] = dp[j - v][p2++] + w;
                }
                if (t > K) break;
            }
            // 更新背包容量为 j 时的前 k 优解
            temp[0] = t - 1;
            memcpy(dp[j], temp, sizeof(int) * t);
        }
    }
    int ans = 0;
    for (int i = 1; i <= K; ++i) {
        ans += dp[V][i];
    }
    cout << ans << endl;
    return 0;
}