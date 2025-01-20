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

// dp状态: dp[i] 表示从第一个字符到第i个字符最少要切多少刀可以全部划分成回文串
// 状态转移推导: 枚举最后一刀的位置 k，k + 1 到末尾部分一定是回文串，1～k 的部分用 dp[k] 来表示
// 状态转移方程（区间dp）: dp[i] = min(dp[k] + 1), k + 1 ~ i 是回文串

#define MAX_N 500000
char s[MAX_N + 5];
int dp[MAX_N + 5] = {0};
vector<int> g[MAX_N + 5]; // g[i][j] 存储了能与 i 位置构成回文串位置的前一个位置

int is_palindrome(int i, int j) {
    while (i < j) {
        if (s[i] != s[j]) return 0;
        ++i;
        --j;
    }
    return 1;
}

void extract(int i, int j) {
    while (s[i] == s[j]) {
        g[i].push_back(j - 1);
        i++;
        j--;
    }
    return;
}

int main() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    // 分别提取奇数位的回文串和偶数位的回文串
    for (int i = 1; i <= n; ++i) {
        extract(i, i);
        extract(i, i + 1);
    }
    dp[0] = -1; // 初始化逻辑加入枚举
    for (int i = 1; s[i]; ++i) {
        dp[i] = i; // 最坏情况，长度为 i 的字符串分成 i 个字符
        // if (is_palindrome(1, i)) { // 如果 1 ~ i 本身就是回文串，i位置不用切
        //     dp[i] = 0;
        //     continue;
        // }
        // 枚举最后一刀的位置
        // for (int j = 1; j < i; ++j) {
        // 转移过程优化
        // 优化1: 从 0 开始枚举，如果此时 1 ～ i 为回文串，则 dp[i] = dp[0] + 1 = 0，符合逻辑
        // 优化2: 从提前记录的有回文串的前一位置去枚举，减少枚举次数
        for (auto j : g[i]) {
            // if (!is_palindrome(j + 1, i)) { // 后置位为回文串才有效
            //     continue;
            // }
            dp[i] = min(dp[i], dp[j] + 1);
        }
    }
    cout << dp[n] << endl;
    return 0;
}