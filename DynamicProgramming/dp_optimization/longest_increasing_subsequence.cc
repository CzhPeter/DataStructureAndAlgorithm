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
// 状态转移优化:
// 定义 len[j]， 一个动态更新的数组，记录长度为 j 的序列的末尾最小值，
// 此时我们在枚举 i 位置的时候，可以利用 len 数组的信息，当 len[k] < val[i] 时，
// 说明 i 位置可以接在长度最长为 k 的序列后面，此时 dp[i] = k + 1，并更新 len[dp[i]] = val[i]
// 找 k 的过程可以使用二分法优化时间复杂度

#define MAX_N 1000000
int len[MAX_N + 5];
int dp[MAX_N + 5] = {0};

int binary_search(int *len, int n, int x) {
    int head = 0, tail = n, mid;
    while (head < tail) {
        mid = (head + tail + 1) >> 1;
        if (len[mid] < x) head = mid;
        else tail = mid - 1;
    }
    return head;
}

int main() {
    int n, ans = 0;
    cin >> n;
    len[0] = -1;
    for (int i = 0, a; i < n; ++i) {
        cin >> a;
        dp[i] = binary_search(len, ans, a) + 1;
        len[dp[i]] = a;
        if (dp[i] > ans) {
            ans = dp[i];
        }
    }
    cout << ans << endl;
    return 0;
}