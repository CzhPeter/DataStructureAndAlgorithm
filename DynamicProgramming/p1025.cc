/*
将整数 n 分成 k 份，且每份不能为空，任意两个方案不相同（不考虑顺序）。
例如：n=7，k=3，下面三种分法被认为是相同的。
1,1,5;
1,5,1;
5,1,1.
问有多少种不同的分法。
输入格式:
n,k （6<n≤200，2≤k≤6）
输出格式:
1 个整数，即不同的分法。
样例输入:
7 3
样例输出:
4
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// 递推状态: f[i][j] 将数字 i 分成 j 份的方案总数
// 容斥原理推导: 方案总数 = 包含数字1的方案总数 + 不包含数字1的方案总数
// 包含数字1的方案总数推导: 方案中如果去掉数字1，就是 i - 1 分成 j - 1 份的方案总数
// 不包含数字1的方案总数推导: 方案中每个数字都减掉1，就是 i - j 分成 j 份的方案总数 
// 递推公式: f[i][j] = f[i - 1][j - 1] + f[i - j][j]
// 边界条件: f[i][1] = 1, f[2][2] = f[1][1] + f[0][2] = 1, f[0][j] = 0
// f[1][1] = f[0][0] + f[0][1] = 1, f[0][0] = 1

#define MAX_N 200
#define MAX_K 6

int f[MAX_N + 5][MAX_K + 5] = {0};

int main() {
    int n, k;
    cin >> n >> k;
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        f[i][1] = 1;
        for (int j = 2, J = min(i, k); j <= J; ++j) {
            f[i][j] = f[i - 1][j - 1] + f[i - j][j];
        }
    }
    cout << f[n][k] << endl;
    return 0;
}