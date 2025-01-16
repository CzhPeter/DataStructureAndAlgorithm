/*
有一个数字序列，求其中最长严格上升子序列的长度
输入:
输入一个数字n (1≤n≤1000000)，代表数字序列的长度。
后跟 n 个整数，第 i 个整数 ai(1≤ai≤10000)，代表数字序列中的第 i 个值。
输出:
输出一个整数，代表所求的最长严格上升子序列的长度。
样例输入:
10
3 2 5 7 4 5 7 9 6 8
样例输出:
5
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// 动归状态: dp[i] 以第 i 位作为结尾的最长上升子序列长度
// 状态转移方程: 
// 如果最长上升子序列 i 前面一位是 j 的话，j < i，val[j] < val[i]，
// 那么只要选择 dp[j] 中最大的，后面再接个 i 就是 dp[i]（长度加1）
// dp[i] = max{dp[j]} + 1, 1 <= j <= i - 1, val[j] < val[i]

#define MAX_N 1000000
int val[MAX_N + 5];
int dp[MAX_N + 5] = {0};
int pre[MAX_N + 5]; // pre[i] = j 表示 i 位置接在 j 位置的后面

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> val[i];
    }
    val[0] = INT32_MIN;
    int ans = 0, ind;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (val[j] >= val[i]) continue;
            if (dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                pre[i] = j;
            }
        }
        if (dp[i] > ans) {
            ans = dp[i];
            ind = i;
        }
    }
    cout << ans << endl;
    while (ind) {
        printf("%d(%d)->", ind, val[ind]);
        ind = pre[ind];
    }
    cout << endl;
    return 0;
}