/*
“低价购买”这条建议是在奶牛股票市场取得成功的一半规则。
要想被认为是伟大的投资者，你必须遵循以下的问题建议:“低价购买；再低价购买”。
每次你购买一支股票,你必须用低于你上次购买它的价格购买它。买的次数越多越好!
你的目标是在遵循以上建议的前提下，求你最多能购买股票的次数。
你将被给出一段时间内一支股票每天的出售价，你可以选择在哪些天购买这支股票。
每次购买都必须遵循“低价购买；再低价购买”的原则。写一个程序计算最大购买次数。
输入格式:
第一行共一个整数 N (1≤N≤5000)，股票发行天数
第二行一行 N 个整数，是每天的股票价格。保证是大小不超过 2^16 的正整数。
输出格式:
输出共一行两个整数，分别为最大购买次数和拥有最大购买次数的方案数（数据保证≤2^31）
当二种方案“看起来一样”时（就是说它们构成的价格队列一样的时候）,这 2 种方案被认为是相同的。
样例输入:
12
68 69 54 64 68 64 70 67 78 62 98 87
样例输出:
4 2
*/

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

// 问题等价: 
// 第一问: 最大购买次数 = 求最长下降子序列的长度
// 第二问: 假设 dp[i] 为最长下降子序列的长度，并在枚举中由 dp[j] 转移得到
// 拥有最大购买次数的方案数 = 所有的合法的 j 位置转移到 i 位置的方案数总额
// 剔除重复方案: 
// 假设 j < i, dp[i] == dp[j] 且 val[i] == val[j] 时，
// dp[j] 对应的方案完全被包含在了 dp[i] 对应的方案内，可以把 f[j] 置 0

#define MAX_N 5000
int dp[MAX_N + 5]; // dp状态: 以 i 位置元素为结尾的最长下降子序列的长度
int val[MAX_N + 5]; // 存储股票的价格
int f[MAX_N + 5]; // f[i] 代表以 i 位置最为结尾的最长下降子序列的数量

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> val[i];
    }
    int max_len = 0;
    val[0] = INT32_MAX;
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (val[j] <= val[i]) {
                continue;
            }
            // 状态转移: 如果 j < i && val[j] > val[i]，那么 dp[i] = max(dp[j]) + 1
            // dp[i] 对应的子序列，即为以 val[j] 为结尾的最长下降子序列，末尾加上 val[i]
            dp[i] = max(dp[i], dp[j] + 1);
        }
        max_len = max(max_len, dp[i]);
        for (int j = 0; j < i; ++j) {
            if (val[j] < val[i]) continue;
            if (val[j] > val[i] && dp[j] + 1 == dp[i]) { 
                // 说明 dp[i] 是由该 j 位置转移得来的，且方案不重复
                f[i] += f[j]; // 方案数累加
            } else if (val[j] == val[i] && dp[j] == dp[i]) {
                f[j] = 0; // 剔除重复方案
            }
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (dp[i] == max_len) {
            cnt += f[i];
        }
    }
    cout << max_len << " " << cnt << endl;
    return 0;
}