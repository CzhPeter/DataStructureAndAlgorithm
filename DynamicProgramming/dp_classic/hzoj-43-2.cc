/*
有一个由数字组成的三角形数塔，站在上一层的某个点，只能到达其下方左右的两个点。
现在请找到一条从上到下的路径，使得路径上所有数字相加之和最大
输入:
第一行输入一个数字 n（1≤n≤1000）
代表数塔层数
接下来n行，按数塔图形，每行有一个或多个的整数，表示该层节点的值（节点值≤100000）
输出:
输出一个整数，代表从上到下路径上所有数字相加和的最大值。
样例输入:
6
3
9 5
4 2 1
3 4 9 6
3 5 3 7 3
2 1 3 9 3 2
样例输出:
39
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// 递推状态: f[i][j] 表示从顶点走到(i, j)点所能获得的最大值
// 递推公式: f[i][j] = max(f[i - 1][j], f[i - 1][j - 1]) + val[i][j]
// 解读: 顶点到(i, j)点上一层的左右两个点的最大值，加上(i, j)点本身的值

#define MAX_N 1000
int val[MAX_N + 5][MAX_N + 5];
int f[MAX_N + 5][MAX_N + 5];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            cin >> val[i][j];
        }
    }
    f[1][1] = val[1][1]; // 初始化顶点值
    for (int i = 2; i <= n; ++i) {
        for (int j = 2; j <= i - 1; ++j) {
            f[i][j] = max(f[i - 1][j - 1], f[i - 1][j]) + val[i][j];
        }
        f[i][1] = f[i - 1][1] + val[i][1];
        f[i][i] = f[i - 1][i - 1] + val[i][i];
    }
    int ans = f[n][1];
    for (int i = 2; i <= n; ++i) {
        if (f[n][i] > ans) {
            ans = f[n][i];
        }
    }
    cout << ans << endl;
    return 0;
}