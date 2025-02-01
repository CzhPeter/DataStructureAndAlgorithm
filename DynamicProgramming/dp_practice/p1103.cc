/*
书架的不整齐度是这样定义的：每两本书宽度的差的绝对值的和。例如有 
4 本书：
1×2
5×3
2×4
3×1
那么 Frank 将其排列整齐后是：
1×2
2×4
3×1
5×3
不整齐度就是 2+3+2=7。
已知每本书的高度都不一样，请你求出去掉 k 本书后的最小的不整齐度。
输入格式:
第一行两个数字 n 和 k，代表书有几本，从中去掉几本（1≤n≤100,1≤k<n）。
下面的 n 行，每行两个数字表示一本书的高度和宽度，均小于等于 200。
保证高度不重复
输出格式:
一行一个整数，表示书架的最小不整齐度。
样例输入:
4 1
1 2
2 4
3 1
5 3
样例输出:
3
*/

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

// dp状态: dp[i][k] 代表第 i 本书必须选的情况下，前 i 本书选择 k 本的最小不整齐度
// 状态转移: dp[i][k] = min(dp[j][k - 1] + |y[i] - y[j]|)
// 即前 j 本选 k - 1 本的最小不整齐度中的最小值，加上 j 和 i 之间的不整齐度

#define MAX_N 100
struct Data {
    int x, y; // x 高，y 宽
} arr[MAX_N + 5];
int dp[MAX_N + 5][MAX_N + 5];

int main() {
    int n, K;
    cin >> n >> K;
    K = n - K; // 去掉 K 本等价于选择 n - K 本
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i].x >> arr[i].y;
    }
    // 按照高度对书排序
    sort(arr + 1, arr + n + 1, [](const Data &a, const Data &b) {
        return a.x < b.x;
    });
    // dp 初始化为极大值
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = dp[i][1] = 0;
        for (int k = 2; k <= i; ++k) {
            for (int j = 1; j < i; ++j) {
                dp[i][k] = min(dp[i][k], dp[j][k - 1] + abs(arr[j].y - arr[i].y));
            }
        }
    }
    int ans = 0x7fffffff;
    for (int i = 1; i <= n; ++i) {
        ans = min(ans, dp[i][K]);
    }
    cout << ans << endl;
    return 0;
}