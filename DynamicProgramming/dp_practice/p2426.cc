/*
有 N 个不同的正整数 x1, x2,..., xN 排成一排，
我们可以从左边或右边去掉连续的 i (1≤i≤n) 个数（只能从两边删除数），剩下 N−i 个数，
再把剩下的数按以上操作处理，直到所有的数都被删除为止。
每次操作都有一个操作价值，比如现在要删除从 i 位置到 k 位置上的所有的数。
操作价值为 ∣xi−xk∣ × (k−i+1)，如果只去掉一个数，操作价值为这个数的值。 
问如何操作可以得到最大值，求操作的最大价值。
输入格式:
第一行为一个正整数 N;
第二行有 N 个用空格隔开的 N 个不同的正整数。
输出格式:
一行，包含一个正整数，为操作的最大值
样例输入:
6
54 29 196 21 133 118
样例输出:
768
*/

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

// 问题转化，把原序列拆分成若干段，并且计算每段的价值，找到一种拆分方案能取得最大的价值
// dp状态: dp[i] 代表前 i 个位置进行拆分所能获得的最大价值
// 状态转移: 假设 j < i，前 j 个位置进行拆分所能获得的最大价值，加上 j + 1 到 i 段的操作价值，
// 所有合法 j 位置中所能得到的最大操作价值，即为 dp[i]
// dp[i] = max(dp[j] + |x[i] - x[j + 1]| * (i - j))

#define MAX_N 100
int x[MAX_N + 5];
int dp[MAX_N + 5];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
    }
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i - 1] + x[i]; // i位置单独成段设为初始值
        for (int j = 0; j < i - 1; ++j) {
            dp[i] = max(dp[i], dp[j] + abs(x[j + 1] - x[i]) * (i - j));
        }
    }
    cout << dp[n] << endl;
    return 0;
}