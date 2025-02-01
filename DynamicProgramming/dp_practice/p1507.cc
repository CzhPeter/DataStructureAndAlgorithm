/*
航天飞机的体积有限，当然如果载过重的物品，燃料会浪费很多钱，每件食品都有各自的体积、质量以及所含卡路里。
在告诉你体积和质量的最大值的情况下，请输出能达到的食品方案所含卡路里的最大值，当然每个食品只能使用一次。
输入格式
第一行 2 个整数，分别代表体积最大值 h 和质量最大值 t。
第二行 1 个整数代表食品总数 n。
接下来 n 行每行 3 个数 体积 hi，质量 ti，所含卡路里 ki。
输出格式
一个数，表示所能达到的最大卡路里（int 范围内）
样例输入:
320 350
4
160 40 120
80 110 240
220 70 310
40 400 220
样例输出:
550
*/

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

// dp状态: dp[i][j][k] 前 i 件物品在重量限制为 j 体积限制为 k 的状态下，卡路里的最大值
// 状态转移: 第 i 件物品用 h 表示重量，t 表示体积，K 表示卡路里
// 不选第 i 件物品: dp[i] = dp[i - 1][j][k]
// 选第 i 件物品: ，dp[i] = dp[i - 1][j - h][k - t] + K
// dp[i] = max(dp[i - 1][j][k], dp[i - 1][j - h][k - t] + K)

#define MAX_H 400
#define MAX_T 400
int dp[MAX_H + 5][MAX_T + 5] = {0};

int main() {
    int n, H, T;
    cin >> H >> T;
    cin >> n;
    for (int i = 0, h, t, k; i < n; ++i) {
        cin >> h >> t >> k;
        for (int j1 = H; j1 >= h; --j1) {
            for (int j2 = T; j2 >= t; --j2) {
                dp[j1][j2] = max(dp[j1][j2], dp[j1 - h][j2 - t] + k);
            }
        }
    }
    cout << dp[H][T] << endl;
    return 0;
}