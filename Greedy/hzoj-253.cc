/*
有 C 头奶牛去晒太阳，每头奶牛各自能够忍受的阳光强度有一个最小值和一个最大值，太大就晒伤了，太小奶牛没感觉。
而刚开始的阳光的强度非常大，奶牛都承受不住，奶牛得涂抹防晒霜，
防晒霜的作用是让阳光照在身上的阳光强度固定为某个值。
那么为了不让奶牛烫伤，又不会没有效果。给出了 L 种防晒霜固定的阳光强度和数量，
每头奶牛只能抹一瓶防晒霜，求能够享受晒太阳的奶牛最多有几头。
输入:
第一行输入两个数 C,L。（1≤C,L≤2500）
接下来 C 行，每行两个数表示每头奶牛能接受的阳光强度的最小值和最大值。（均小于 1000）
​再接下来 L 行，每行两个数表示每种防晒霜固定的阳光强度和数量。（均小于 1000）
输出:
​输出能晒太阳的奶牛的最多数量。
样例输入:
3 2
3 10
2 5
1 5
6 2
4 1
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
// 奶牛的晒光强度范围相当于数轴上的若干个线段，防晒霜的固定强度相当于数轴上的一个点，
// 一个点仅能和一条线段配对，即他们有交，求最大配对数
// 贪心策略:
// 将所有点从小到大排序，所有线段按右端点从小到大排序，右端点相同，按照左端点从小到大排序。
// 依次判断点与线段是否匹配。

#define MAX_N 2500

struct Data {
    int a, b;
};

Data cow[MAX_N + 5]; // a, b: 阳光强度区间
Data item[MAX_N + 5]; // b: 防晒固定阳光强度; a: 数量 

bool cmp(const Data &a, const Data &b) {
    if (a.b != b.b) return a.b < b.b;
    return a.a < b.a;
}

int main() {
    int C, L;
    cin >> C >> L;
    for (int i = 0; i < C; ++i) {
        cin >> cow[i].a >> cow[i].b;
    }
    for (int i = 0; i < L; ++i) {
        cin >> item[i].b >> item[i].a;
    }
    sort(cow, cow + C, cmp);
    sort(item, item + L, cmp);
    int ans = 0;
    for (int i = 0; i < C; ++i) {
        int flag = 0;
        for (int j = 0; j < L; ++j) {
            if (item[j].a == 0) continue;
            if (item[j].b <= cow[i].b && item[j].b >= cow[i].a) {
                flag = 1;
                item[j].a -= 1;
                break;
            }
        }
        ans += flag;
    }
    cout << ans << endl;
    return 0;
}