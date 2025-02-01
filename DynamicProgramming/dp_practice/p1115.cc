/*
给出一个长度为 n 的序列 a，选出其中连续且非空的一段使得这段和最大
输入格式:
第一行是一个整数，表示序列的长度 n。
第二行有 n 个整数，第 i 个整数表示序列的第 i 个数字 ai。
输出格式;
输出一行一个整数表示答案。
样例输入:
7
2 -4 3 -1 2 -4 3
样例输出;
4
*/

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

// dp状态: dp[i] 代表以 i 位置为结尾的最大子段和
// 状态转移: dp[i] = max(val[i], dp[i - 1] + val[i])
// 1. i 位置单独成段: dp[i] = val[i]
// 2. i 位置跟前面成段: dp = dp[i - 1] + val[i]
// 可以看出，只要 dp[i - 1] > 0，就是 2 更优

int main() {
    int n, pre_dp = 0, dp, ans = INT32_MIN;
    cin >> n;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        if (pre_dp > 0) dp = pre_dp + x;
        else dp = x;
        ans = max(ans, dp);
        pre_dp = dp;
    }
    cout << ans << endl;
    return 0;
}