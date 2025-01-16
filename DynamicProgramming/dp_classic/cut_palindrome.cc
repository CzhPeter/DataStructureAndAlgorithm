/*
给出一个字符串S，问对字符串S最少切几刀，使得分成的每一部分都是一个回文串（注意：单一字符是回文串）
输入:
一个长度为n(1≤n≤500000)的字符串S，只包含小写字母。
输出:
输出一个整数，代表所切的最少刀数。
样例输入
sehuhzzexe
样例输出
4
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

// 容斥原理推导: 将字符串S最少切几刀分为两种情况: 一刀都不切 = 0刀; 至少切了1刀
// 至少切一刀的情况下，S被分为s1和s2两个字符串，对于s1和s2，如果已知它们各自最少切割成回文串的刀数，
// dp(s) = dp(s1) + dp(s2) + 1
// 区间dp思想: 以字符串的长度作为更新方向: 长度为1的子串的切割刀数 -> 长度为2的子串的切割刀数 -> ... 
// dp状态: dp[i][j] 表示从 i 到 j 最少要切多少刀
// 用k来枚举切割位置: i <= k < j, dp[i][j] = dp[i][k] + dp[k + 1][j] + 1
// S本身是回文串: S[i] == S[j] 且 dp[i + 1][j - 1] == 0
// dp[i][j] = min(dp[i][j] = dp[i][k] + dp[k + 1][j] + 1, 0)

#define MAX_N 1000
char s[MAX_N + 5];
int dp[MAX_N + 5][MAX_N + 5] = {0};

int main() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    for (int l = 1; l <= n; ++l) { // 区间dp: 按字符串长度递推
        for (int i = 1; i <= n - l + 1; ++i) {
            int j = i + l - 1;
            if (s[i] == s[j] && dp[i + 1][j - 1] == 0) {
                dp[i][j] = 0;
            } else {
                dp[i][j] = l;
                for (int k = i; k < j; ++k) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + 1);
                }
            }
        }
    }
    cout << dp[1][n] << endl;
    return 0;
}