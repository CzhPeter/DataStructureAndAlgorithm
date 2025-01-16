/*
给出两个字符串，求其两个的最长公共子序列长度。
输入:
第一行输入一个字符串s1，第二行输入一个字符串s2 (字符串长度≤1000) ，两个字符串长度可以不相同。
输出:
输出一个整数，代表两个字符串的最长公共子序列的长度。
样例输入:
sehuaizexi
yhaizeyiux
样例输出:
6
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

// 动归状态: dp[i][j] 代表A串以i位置为结尾，B串以j位置为结尾的公共子序列长度
// 状态转移方程: 
// A[i] = B[j]，A串取前i-1位的子串，和B串取前j-1位的子串的公共子序列长度，加上1就是dp[i][j]
// A[i] != B[j]，说明要么是A[i]不在公共子序列中 dp[i - 1][j]，要么是B[j]不在公共子序列中，dp[i][j - 1]
// dp = max(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] + (A[i] == B[i]))

#define MAX_N 1000
char s1[MAX_N + 5], s2[MAX_N + 5];
int dp[MAX_N + 5][MAX_N + 5] = {0};

int main() {
    scanf("%s%s", s1 + 1, s2 + 1);
    int n = strlen(s1 + 1), m = strlen(s2 + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if (s1[i] == s2[j]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}