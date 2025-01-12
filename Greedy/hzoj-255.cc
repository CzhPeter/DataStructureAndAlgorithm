/*
地图 x 轴的上方为海，下方为陆地，海中有 n 个小岛，坐标分别为 (Xi,Yi)。
有一种雷达，能探测到的范围为以 d 为半径的圆。问海岸线上至少造多少雷达可以把所有的小岛都处在探测范围内。
注意雷达是建在海岸线上的，也就是x轴上的。
输入:
​第一行输入两个数 n,d。（1≤n≤1000）
​接下来 n 行，每行两个数代表小岛的坐标。（−1000≤Xi,Yi≤1000）
输出
输出一个数表示答案，无解时输出 −1。
样例输入:
3 2
1 2
-3 1
2 1
样例输出:
2
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// 问题转化:
// x轴上划分若干个区间，使得区间内的点到某个岛屿的距离<=d，
// 此时每个区间内至少放置一个雷达即可
// 贪心策略:
// 按照区间[li, ri]结束位置从小到大排序，雷达放置在区间末尾，pos代表最后一个雷达的位置，
// 若pos < li，雷达数量+1，pos=ri

#define MAX_N 1000

struct Range {
    double l, r;  
} arr[MAX_N + 5];

bool cmp(const Range &a, const Range &b) {
    return a.r < b.r;
}

int main() {
    int n;
    double r, x, y, pos;
    cin >> n >> r;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        if (y > r) {
            cout << -1 << endl;
            return 0;
        }
        double delta = sqrt(r * r - y * y);
        arr[i].l = x - delta;
        arr[i].r = x + delta;
    }
    sort(arr, arr + n, cmp);
    int ans = 1;
    pos = arr[0].r;
    for (int i = 1; i < n; ++i) {
        if (arr[i].l > pos) {
            ans += 1;
            pos = arr[i].r;
        }
    }
    cout << ans << endl;
    return 0;
}