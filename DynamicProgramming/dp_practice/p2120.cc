/*
L 公司有 n 个工厂，由高到低分布在一座山上，工厂 1 在山顶，工厂 n 在山脚。
由于这座山处于高原内陆地区（干燥少雨），L公司一般把产品直接堆放在露天，以节省费用。
突然有一天，L 公司的总裁 L 先生接到气象部门的电话，被告知三天之后将有一场暴雨，于是 L 先生决定紧急在某些工厂建立一些仓库以免产品被淋坏。
由于地形的不同，在不同工厂建立仓库的费用可能是不同的。
第 i 个工厂目前已有成品 pi 件，在第 i 个工厂位置建立仓库的费用是 ci 。
对于没有建立仓库的工厂，其产品应被运往其他的仓库进行储藏，
而由于 L 公司产品的对外销售处设置在山脚的工厂 n，
故产品只能往山下运（即只能运往编号更大的工厂的仓库），
当然运送产品也是需要费用的，一件产品运送一个单位距离的费用是 1。
假设建立的仓库容量都都是足够大的，可以容下所有的产品。你将得到以下数据：
1. 工厂 i 距离工厂 1 的距离 xi（其中 x1 = 0）。
2. 工厂 i 目前已有成品数量 pi。
3. 在工厂 i 建立仓库的费用 ci。
请你帮助 L 公司寻找一个仓库建设的方案，使得总的费用（建造费用 + 运输费用）最小。
输入格式:
输入的第一行是一个整数 n，代表工厂的个数。
第 2 到 (n+1) 行，每行有三个用空格隔开的整数，第 (i+1) 行的整数依次代表 xi,pi,ci。
输出格式:
仅输出一行一个整数，代表最优方案的费用。
样例输入:
3
0 5 10
5 3 100
9 6 10
样例输出:
32
*/

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

// dp状态: dp[i] 代表前 i 个位置，在 i 建仓库的最小代价
// 状态转移: 
// 假设 j < i, j 位置为上一个仓库位置，则 j + 1 ~ i 这一段位置的货物都要存放到 i 位置上
// dp[i] = min(dp[j] + T + ci)，T 代表 j + 1 ~ i 货物运送到 i 位置上的运送费用总和
// T = (xi - xk) * pk, j + 1 <= k <= i 的和
// 上述式子可以等于 xi * (pk 的区间和) - ((xk * pk) 的区间和))
// 令(pk 的前缀和)为s，(xk * pk)的前缀和为t，则 T = xi * (si - sj) - (ti - tj)
// dp[i] = min(dp[j] + xi * (si - sj) - (ti - tj) + ci)
// 得到 (dp[j] + tj) - (xi * sj) + (xi * si - ti + ci)
//         查找值        混合值             固定值
// 可以使用斜率优化技巧
// 如果 j 优于 k，则 dp[j] + tj - (dp[k] + tk) < xi * (sj - sk)，令 dp[x] + tx = fx
// 斜率 = (fj - fk) / (sj - sk) < xi，维护斜率单调上升的集合

#define MAX_N 1000000
long long dp[MAX_N + 5];
long long c[MAX_N + 5], x[MAX_N + 5];
long long s[MAX_N + 5]; // pk 的前缀和
long long t[MAX_N + 5]; // xk * pk 的前缀和
long long f[MAX_N + 5]; // f[i] = dp[i] + t[i]
long long q[MAX_N + 5], head = 0, tail = 0;

void set(long long i, long long j) {
    dp[i] = dp[j] + x[i] * (s[i] - s[j]) - (t[i] - t[j]) + c[i];
    f[i] = dp[i] + t[i];
    return;
}

int main() {
    long long n;
    cin >> n;
    for (long long i = 1; i <= n; ++i) {
        cin >> x[i] >> s[i] >> c[i];
        // 初始化前缀和数组
        t[i] = t[i - 1] + x[i] * s[i];
        s[i] += s[i - 1];
    }
    set(1, 0);
    q[tail++] = 0;
    q[tail++] = 1;
    for (long long i = 2; i <= n; ++i) {
        // 弹出队头不满足斜率条件的点
        do {
            long long X = s[q[head + 1]] - s[q[head]];
            long long Y = f[q[head + 1]] - f[q[head]];
            if (tail - head >= 2 && Y < x[i] * X) ++head;
            else break;
        } while (1);
        set(i, q[head]);
        // 维护队列的单调性
        do {
            long long A = f[i] - f[q[tail - 1]];
            long long B = f[q[tail - 1]] - f[q[tail - 2]];
            long long C = s[i] - s[q[tail - 1]];
            long long D = s[q[tail - 1]] - s[q[tail - 2]];
            if (tail - head >= 2 && A * D < B * C) {
                --tail;
            } else {
                break;
            }
        } while(1);
        q[tail++] = i;
    }
    long long ans = dp[n];
    for (long long i = n - 1; i >= 1 && s[i] == s[i + 1]; --i) {
        ans = min(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}