/*
小明过生日的时候，爸爸送给他一副乌龟棋当作礼物。
乌龟棋的棋盘是一行 N 个格子，每个格子上一个分数（非负整数）。棋盘第 1 格是唯一的起点，第 N 格是终点，
游戏要求玩家控制一个乌龟棋子从起点出发走到终点。
乌龟棋中 M 张爬行卡片，分成 4 种不同的类型（M 张卡片中不一定包含所有 4 种类型的卡片，见样例），
每种类型的卡片上分别标有 1,2,3,4 四个数字之一，表示使用这种卡片后，乌龟棋子将向前爬行相应的格子数。
游戏中，玩家每次需要从所有的爬行卡片中选择一张之前没有使用过的爬行卡片，
控制乌龟棋子前进相应的格子数，每张卡片只能使用一次。
游戏中，乌龟棋子自动获得起点格子的分数，并且在后续的爬行中每到达一个格子，就得到该格子相应的分数。
玩家最终游戏得分就是乌龟棋子从起点到终点过程中到过的所有格子的分数总和。
很明显，用不同的爬行卡片使用顺序会使得最终游戏的得分不同，小明想要找到一种卡片使用顺序使得最终游戏得分最多。
现在，告诉你棋盘上每个格子的分数和所有的爬行卡片，你能告诉小明，他最多能得到多少分吗？
输入格式:
每行中两个数之间用一个空格隔开。
第 1 行 2 个正整数 N,M，分别表示棋盘格子数和爬行卡片数。
第 2 行 N 个非负整数，a1,a2,…,aN，其中 ai 表示棋盘第 i 个格子上的分数。
第 3 行 M 个整数，b1,b2,…,bM，表示 M 张爬行卡片上的数字。
输入数据保证到达终点时刚好用光 M 张爬行卡片。
输出格式:
一个整数，表示小明最多能得到的分数。
样例输入:
9 5
6 10 14 2 8 8 18 5 17
1 3 1 2 1
样例输出:
73
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

// 动归状态: dp[a][b][c][d] 代表步数为1的卡片用了a张，步数为2的卡片用了b张，
// 步数为3的卡片用了c张，步数为4的卡片用了d张后，所能获得的最大值
// 状态转移方程:
// 经过上述状态到达的终点 s = a + 2 * b + 3 * c + 4 * d，枚举最后一张卡片用的是哪种卡片，
// 如果用 a，上一个状态是 dp[a - 1][b][c][d]，则 dp[a][b][c][d] = dp[a - 1][b][c][d] + val[s]
// 同理用 b/c/d，对应的位置改为 b - 1 / c - 1 / d - 1
// 最后取最大值，即为状态转移方程

#define MAX_N 40
// int dp[MAX_N + 5][MAX_N + 5][MAX_N + 5][MAX_N + 5];
// 优化空间复杂度: 
// 去除冗余状态: dp[b][c][d]更新前就是dp[a - 1][b][c][d]，更新后就是dp[a][b][c][d]
int dp[MAX_N + 5][MAX_N + 5][MAX_N + 5];
int val[400]; // 记录棋盘格的分值
int cnt[4]; // 记录每种卡片的数量

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> val[i];
    }
    for (int i = 0, a; i < m; ++i) {
        cin >> a;
        cnt[a - 1] += 1;
    }
    // 状态转移
    for (int a = 0; a <= cnt[0]; ++a) {
        for (int b = 0; b <= cnt[1]; ++b) {
            for (int c = 0; c <= cnt[2]; ++c) {
                for (int d = 0; d <= cnt[3]; ++d) {
                    int s = a + 2 * b + 3 * c + 4 * d;
                    // int ans = 0;
                    int ans = dp[b][c][d];
                    // if (a) ans = max(ans, dp[a - 1][b][c][d]);
                    // if (a) ans = max(ans, dp[a][b - 1][c][d]);
                    if (b) ans = max(ans, dp[b - 1][c][d]);
                    // if (a) ans = max(ans, dp[a][b][c - 1][d]);
                    if (c) ans = max(ans, dp[b][c - 1][d]);
                    // if (a) ans = max(ans, dp[a][b][c][d - 1]);
                    if (d) ans = max(ans, dp[b][c][d - 1]);
                    // dp[a][b][c][d] = ans + val[s];
                    dp[b][c][d] = ans + val[s];
                }
            }
        }
    }
    // cout << dp[cnt[0]][cnt[1]][cnt[2]][cnt[3]] << endl;
    cout << dp[cnt[1]][cnt[2]][cnt[3]] << endl;
    return 0;
}