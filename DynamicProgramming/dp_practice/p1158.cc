/*
经过 11 年的韬光养晦，某国研发出了一种新的导弹拦截系统，
凡是与它的距离不超过其工作半径的导弹都能够被它成功拦截。
当工作半径为 0 时，则能够拦截与它位置恰好相同的导弹。
但该导弹拦截系统也存在这样的缺陷：每套系统每天只能设定一次工作半径。
而当天的使用代价，就是所有系统工作半径的平方和。
某天，雷达捕捉到敌国的导弹来袭。由于该系统尚处于试验阶段，所以只有两套系统投入工作。
如果现在的要求是拦截所有的导弹，请计算这一天的最小使用代价。
输入格式:
第一行包含 4 个整数 x1,y1,x2,y2，每两个整数之间用一个空格隔开，
表示这两套导弹拦截系统的坐标分别为 (x1,y1), (x2,y2)。
第二行包含 1 个整数 N，表示有 N 颗导弹。
接下来 N 行，每行两个整数 x,y，中间用一个空格隔开，表示一颗导弹的坐标 (x,y)。不同导弹的坐标可能相同。
输出格式:
一个整数，即当天的最小使用代价。
样例输入:
0 0 10 0
2
-3 3
10 0
样例输出:
18
*/

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

// 问题思路，对所有导弹距离第一个拦截系统的距离排序，找到第一个拦截系统能拦截的最远导弹，
// 然后剩下的导弹中找距离第二个拦截系统最远的导弹，两者的代价和就是最小代价

#define MAX_N 100000
int x[MAX_N + 5], y[MAX_N + 5], ind[MAX_N + 5];
int n, x_1, y_1, x_2, y_2;
int dis[MAX_N + 5]; // dis[i] 表示从 i 位置往后，距离第二个拦截系统的最远距离

#define DIS(x_1, y_1, x_2, y_2) static_cast<int>(pow(x_1 - x_2, 2) + pow(y_1 - y_2, 2))

bool cmp(int i, int j) {
    return DIS(x[i], y[i], x_1, y_1) < DIS(x[j], y[j], x_1, y_1);
}

int main() {
    cin >> x_1 >> y_1 >> x_2 >> y_2;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        ind[i] = i;
    }
    sort(ind, ind + n, cmp);
    for (int i = n - 1; i >= 0; --i) {
        dis[i] = DIS(x[ind[i]], y[ind[i]], x_2, y_2);
        dis[i] = max(dis[i + 1], dis[i]);
    }
    int ans = dis[0];
    for (int i = 0; i < n; ++i) {
        ans = min(ans, DIS(x[ind[i]], y[ind[i]], x_1, y_1) + dis[i + 1]);
    }
    cout << ans << endl;
    return 0;
}