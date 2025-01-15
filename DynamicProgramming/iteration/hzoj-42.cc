/*
某个国家的货币系统中，有 m 种面额的钱币，现在要用这 m 种面额的钱币凑足 n 元钱，问一共有多少种方法。
m 种钱币不一定要都被用到。
例如，有 3 种钱币，分别为1、2、5，那么有四种方法拼凑出5元钱
1. (1，1，1，1，1) 全是1元钱
2. (1，2，2)，(1，1，1，2) 使用1元和2元
3. (5) 只用5元钱
注意：方案中的钱币不分顺序，也就是说（1，2，2） 和（2，1，2）是同一种方法。
输入:
输入两个数字 m, n（1≤m≤20,200≤n≤10000），
第二行 m 个数字，代表 m 种钱币的面额，钱币面额大于0，数据中保证 m 种钱币各不相同。
输出:
输出一个整数，代表拼凑出 n 元钱的方法数，答案有可能过大，请对 9973 取余。
样例输入:
8 200
1 2 5 10 20 50 100 200
样例输出:
3871
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// 递推状态:
// f[i][j]代表: 用前i种钱币，凑足j元钱的方法总数，设val[i]代表i钱币的面值
// 把f[i][j]分成两个不相交的子集: 
// 1. 没有使用第i种钱币的方法: f[i - 1][j]
// 2. 使用了第i种钱币的方法: f[i][j - val[i]]
// 递推公式: f[i][j] = f[i - 1][j] + f[i][j - val[i]]

#define MAX_N 10000
#define MAX_M 20
int val[MAX_M + 5];
int f[MAX_M + 5][MAX_N + 5];

int main() {
    int m, n;
    cin >> m >> n;
    for (int i = 1; i <= m; ++i) {
        cin >> val[i];
    }
    for (int i = 1; i <= m; ++i) {
        f[i][0] = 1;
        for (int j = 1; j <= n; ++j) {
            f[i][j] = f[i - 1][j];
            if (j < val[i]) { // 用不了第i种钱币的情况，即第i种钱币已经超出n值
                continue;
            }
            f[i][j] += f[i][j - val[i]];
            f[i][j] %= 9973;
        }
    }
    cout << f[m][n] << endl;
    return 0;
}
