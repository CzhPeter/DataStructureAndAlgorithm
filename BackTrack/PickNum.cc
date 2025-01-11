/*
已知 n 个整数 x1,x2,⋯,xn，以及 1 个整数 k（k<n）。
从 n 个整数中任选 k 个整数相加，可分别得到一系列的和。
例如当 n=4，k=3，4 个整数分别为 3,7,12,19 时，可得全部的组合与它们的和为：
3+7+12=22
3+7+19=29
7+12+19=38
3+12+19=34
现在，要求你计算出和为素数共有多少种。
例如上例，只有一种的和为素数：3+7+19=29。
输入格式: 
第一行两个空格隔开的整数 n,k（1≤n≤20，k<n）。
第二行 n 个整数，分别为 x1,x2,⋯,xn（1≤xi≤5×10^6）。
输出格式: 
输出一个整数，表示种类数。
样例输入:
4 3
3 7 12 19
样例输出: 
1
*/

#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 20
int val[MAX_N + 5];
long long ans = 0;

int is_prime(int x) {
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) return 0;
    }
    return 1;
}

// 参数说明：
// k: 当前已经选了 k 个数
// index: 当前可以选的第一个数据下标
// n: 共有 n 个数
// m: 最多可以选 m 个数
// sum: 当前的和值
void dfs(int k, int index, int n, int m, int sum) {
    if (k == m) {
        if (is_prime(sum)) {
            ans += 1;
        }
        return;
    }
    for (int i = index; i <= n; ++i) {
        // select i
        dfs(k + 1, i + 1, n, m, sum + val[i]);
    }
    return;
}

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> val[i];
    }
    dfs(0, 1, n, k, 0);
    cout << ans << endl;
    return 0;
}