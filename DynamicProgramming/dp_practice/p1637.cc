/*
Erwin 最近对一种叫 thair 的东西巨感兴趣。。。
在含有 n 个整数的序列 a1,a2,…,an 中，三个数被称作thair当且仅当 i<j<k 且 ai<aj<ak。
求一个序列中 thair 的个数。
输入格式:
开始一行一个正整数 n,
以后一行 n 个整数 a1,a2,…,an。
输出格式:
一行一个整数表示 thair 的个数。
样例输入:
4
2 1 3 4
样例输出:
2
*/

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

// dp状态: dp[i][3] 代表以 i 为结尾的 1/2/3 元上升子序列的数量
// 只要 j < i, val[j] < val[i]，那么 dp[i][3] = 所有合法的dp[j][2]之和

#define MAX_N 30000
int n, a[MAX_N + 5];
long long f[MAX_N + 5][4];

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        f[i][1] = 1;
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            if (a[j] >= a[i]) continue;
            f[i][2] += f[j][1];
            f[i][3] += f[j][2];
        }
        ans += f[i][3]; // 累加所有位置的三元上升序列
    }
    cout << ans << endl;
    return 0;
}