/*
给有一个能承重 V 的背包，和n种物品，每种物品的数量有限多，我们用重量、价值和数量的三元组来表示一个物品，
第 i 件物品表示为（Vi，Wi，Si），问在背包不超重的情况下，得到物品的最大价值是多少？
输入:
第一行输入两个数V、n，分别代表背包的最大承重和物品种类数。
接下来 n 行，每行三个数 Vi、Wi、Si，分别代表第 i 种物品的重量、价值和数量。
输出:
输出一个整数，代表在背包不超重情况下所装物品的最大价值。
样例输入:
15 4
4 10 5
3 7 4
12 12 2
9 8 7
样例输出:
37
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// 把一个物品的数量属性，看成是由多个相同物品，把问题转化成0/1背包来做

#define MAX_V 100000
int dp[MAX_V + 5] = {0};

int main() {
    int V, n;
    cin >> V >> n;
    for (int i = 1, v, w, s; i <= n; ++i) {
        cin >> v >> w >> s;
        for (int k = 0; k < s; ++k) {
            for (int j = V; j >= v; --j) {
                dp[j] = max(dp[j], dp[j - v] + w);
            }
        }
    }
    cout << dp[V] << endl;
    return 0;
}