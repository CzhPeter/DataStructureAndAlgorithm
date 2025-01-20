/*
有一台古老的打字机和一篇待打印的文章，文章中有 n 个字符，每个字符会有一个消耗值 Ci
, 打字机工作一次会打印若干连续的 k 个字符，同时打字机会有磨损，打字机的单次磨损计算公式为：
(begin+k−1)∑(i=begin)Ci)^2+M
其中 M 是打字机启动一次的固定磨损值，现在给你 n 个字符的消耗值，
问你打字机顺序打印出这 n 个字符的最小磨损值为多少？
输入:
第一行输入两个数字，n,M(1≤n≤106,1≤M≤104) 代表文章中字符数量和打字机单次启动的固定磨损值。
第二行输入 n 个数字，第 i 个数字代表文章中第 i 个字符的磨损值 Ci(1≤Ci≤100)。
输出:
输出一个整数，代表打字机顺序打完 n 个字符的最小磨损值
样例输入:
6 40
3 3 6 5 1 2
样例输出:
256
*/

#include <iostream>
#include <vector>
#include <deque>
#include <stack>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// dp状态: dp[i] 表示打印到第 i 个字符的最小消耗
// 状态转移方程: 最后一段打印的起始位置为 j + 1，之前的消耗为 dp[j]，
// 最后一段消耗为 (sum[i] - sum[j])^2 + M，sum数组代表前缀和
// dp[i] = min(dp[j] + (sum[i] - sum[j])^2 + M), 0 <= j < i - 1
// 展开原来的状态转移方程可得到: 
// dp[i] = min(dp[j] + sum[j]^2 - 2 * sum[i] * sum[j] + sum[i]^2 + M)
// 其中不确定的值是 dp[j] + sum[j]^2，混合值是 sum[i] * sum[j]
// 可使用斜率优化技巧规避混合值: 
// 假设 i 点通过 j, k 转移，j 优于 k 且 k < j，则 
// dp[j] + sum[j]^2 - 2 * sum[i] * sum[j] + sum[i]^2 + M < dp[k] + sum[k]^2 - 2 * sum[i] * sum[k] + sum[i]^2 + M
// dp[j] + sum[j]^2 - 2 * sum[i] * sum[j] < dp[k] + sum[k]^2 - 2 * sum[i] * sum[k]
// (dp[j] + sum[j]^2 - dp[k] - sum[k]^2) / (sum[j] - sum[k]) < 2 * sum[i]
// 令 f[x] = dp[x] + sum[x]^2，即 (f[j] - f[k]) / (sum[j] - sum[k]) < 2 * sum[i]，
// 这样就可以把不等式左边看成是 (sum[j], f[j]) 和 (sum[k], f[k]) 之间的斜率
// 两点之间，只要斜率小于 2 * sum[i]，就可以确定哪个点更优，
// 此时列出三个点之间的斜率变化和 2 * sum 的关系，就可以确定斜率变化的单调性，并在遍历时剔除不符合斜率变化单调性的点
// 单调性维护和剔除操作可以由单调队列完成

#define MAX_N 1000000
#define SQ(x) ((x) * (x))
long long c[MAX_N + 5], sum[MAX_N + 5];
long long dp[MAX_N + 5], f[MAX_N + 5];
int q[MAX_N + 5], head, tail;
long long n, M;

double slope(int i, int j) {
    return 1.0 * (f[i] - f[j]) / (sum[i] - sum[j]);
}

void set(int i, int j) {
    dp[i] = dp[j] + SQ(sum[i] - sum[j]) + M;
    f[i] = dp[i] + SQ(sum[i]);
    return;
}

int main() {
    cin >> n >> M;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
        sum[i] = sum[i - 1] + c[i];
    }
    head = tail = 0;
    q[tail++] = 0;
    for (int i = 1; i <= n; ++i) {
        while (tail - head >= 2 && slope(q[head + 1], q[head]) < 2 * sum[i]) {
            head += 1;
        }
        set(i, q[head]);
        while (tail - head >= 2 && slope(q[tail - 1], q[tail - 2]) > slope(i, q[tail - 1])) {
            tail -= 1;
        }
        q[tail++] = i;
    }
    cout << dp[n] << endl;
    return 0;
}