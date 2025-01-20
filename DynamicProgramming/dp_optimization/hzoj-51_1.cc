/*
在一个黑白相间的矩形中，问有多少个全白色的子矩形。
输入:
第一行输入两个数字 n,m（2≤n,m≤1000），代表矩形的长和宽。
接下来 n 行，每行 m 个数字，0 代表黑色格子，1 代表白色格子。
输出:
输出一个整数，代表全白色子矩形的数量，结果可能过大，输出时请对 100007 取余。
样例输入:
6 6
0 1 1 1 1 1
1 1 0 1 1 1
1 1 1 1 1 1
1 1 1 0 1 1
1 1 1 1 0 1
1 0 1 1 1 1
样例输出:
152
*/

#include <iostream>
#include <vector>
#include <deque>
#include <stack>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// 确定小矩形的方式: 左上角坐标和右下角坐标
// dp状态: dp[i][j] 表示以 (i, j) 点作为左上角坐标的合法全白矩形的数量
// f[i][j] 代表 (i, j) 点向下有多少个连续的白色格子
// 状态转移方程: 
// 合法矩形分块方式: 同一行往右找第一个比当前 f 值小的位置(用单调栈优化查找过程)，
// 该位置前一个位置到当前点为第一块，该位置向后为第二块，以该位置为起点还可以继续向后分块
// 块内矩形数量 = 当前 f 值 * 块长度
// dp[i][j] = f[i][j] * (k - j) + dp[i][k], k 就是第一个 f 值小于当前位置的列位置
// dp[i][j] 只和 k 有关系，所以可以降维成 dp[j]

#define MAX_N 1000
int dp[MAX_N + 5];
int f[MAX_N + 5][MAX_N + 5];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> f[i][j];
        }
    }
    // 从最后一行向上遍历初始化 f 值
    for (int i = n - 1; i >= 1; --i) {
        for (int j = 1; j <= m; ++j) {
            if (f[i][j] == 0) continue;
            f[i][j] += f[i + 1][j];
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        stack<int> s;
        f[i][m + 1] = -1;
        s.push(m + 1);
        for (int j = m; j >= 1; --j) {
            while (f[i][s.top()] >= f[i][j]) {
                s.pop();
            }
            int k = s.top();
            dp[j] = f[i][j] * (k - j) + dp[k];
            dp[j] %= 100007;
            ans += dp[j];
            ans %= 100007;
            s.push(j);
        }
    }
    cout << ans << endl;
    return 0;
}