/*
sqybi 现在看中了 n 个 MM，我们不妨把她们编号 1 到 n。请 MM 吃饭是要花钱的，
我们假设请 i 号 MM 吃饭要花 rmb[i] 块大洋。而希望骗 MM 当自己 GF 是要费人品的，
我们假设请第 i 号 MM 吃饭试图让她当自己 GF 的行为（不妨称作泡该 MM）要耗费 rp[i] 的人品。
而对于每一个 MM 来说，sqybi 都有一个对应的搞定她的时间，
对于第 i 个 MM 来说叫做 time[i]。sqybi 保证自己有足够的魅力用 time[i] 的时间搞定第 i 个 MM ^_^。
sqybi 希望搞到尽量多的 MM 当自己的 GF，这点是毋庸置疑的。
但他不希望为此花费太多的时间（毕竟七夕赛的题目还没出），
所以他希望在保证搞到 MM 数量最多的情况下花费的总时间最少。
sqybi 现在有 m 块大洋,他也通过一段时间的努力攒到了 r 的人品（这次为模拟赛出题也攒 rp 哦~~）。
他凭借这些大洋和人品可以泡到一些 MM。他想知道，自己泡到最多的 MM 花费的最少时间是多少。
注意 sqybi 在一个时刻只能去泡一个 MM ——如果同时泡两个或以上的 MM 的话，她们会打起来的…
输入格式:
输入的第一行是 n，表示 sqybi 看中的 MM 数量。
接下来有 n 行，依次表示编号为 1,2,3,…,n 的一个 MM 的信息。
每行表示一个 MM 的信息，有三个整数：rmb，rp 和 time。
最后一行有两个整数，分别为 m 和 r。
输出格式:
你只需要输出一行，其中有一个整数，表示 sqybi 在保证 MM 数量的情况下花费的最少总时间是多少。
样例输入:
4
1 2 5
2 1 6
2 2 2
2 2 3
5 5
样例输出:
13
*/

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

// 问题类型: 多重限制条件的 0/1 背包问题
// 问题关键点: 维护最优解的过程中如何去维护一个和最优解相关的变量

#define MAX_N 100
int dp[MAX_N + 5][MAX_N + 5];
int dp_min_time[MAX_N + 5][MAX_N + 5];
int rmb[MAX_N + 5], rp[MAX_N + 5], t[MAX_N + 5];

int main() {
    int n, M, R;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> rmb[i] >> rp[i] >> t[i];
    }
    cin >> M >> R;
    for (int i = 0; i < n; ++i) {
        for (int j = M; j >= rmb[i]; --j) {
            for (int k = R; k >= rp[i]; --k) {
                if (dp[j][k] < dp[j - rmb[i]][k - rp[i]] + 1) { // 需要更新dp的情况
                    dp[j][k] = dp[j - rmb[i]][k - rp[i]] + 1; // 更新dp
                    dp_min_time[j][k] = dp_min_time[j - rmb[i]][k - rp[i]] + t[i]; // 更新最短时间
                } else if (dp[j][k] == dp[j - rmb[i]][k - rp[i]] + 1) { // dp值相同时，说明有两组最优解，取时间短的保存
                    dp_min_time[j][k] = min(dp_min_time[j][k], dp_min_time[j - rmb[i]][k - rp[i]] + t[i]);
                }
            }
        }
    }
    cout << dp_min_time[M][R] << endl;
    return 0;
}

