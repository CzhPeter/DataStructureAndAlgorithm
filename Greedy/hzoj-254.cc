/*
有 C 头奶牛需要挤奶，每头奶牛需要在规定的时间开始挤奶，并在规定的时间结束挤奶，
每头奶牛挤奶时会占据一台机器。求 C 头奶牛在规定的时间挤奶至少需要多少台挤奶机。
输入:
​第一行输入一个数 C。（1≤C≤50000）
接下来 C 行，每行两个数表示每头奶牛开始挤奶的时间和结束挤奶的时间。（均小于 1,000,000）
输出:
第一行输出最少需要的机器数量。
​接下来 C 行，每行输出一个数，表示第 i 头奶牛使用的挤奶机编号。（奶牛优先使用编号小的机器）
样例输入:
5
1 10
2 4
3 6
5 8
4 7
样例输出:
4
1
2
3
2
4
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// 贪心策略:
// 按照挤奶开始时间排序，依次将奶牛安排给可以安排的编号最小的挤奶机，
// 当无法安排时，增加挤奶机数量

#define MAX_N 50000

struct Data {
    int l, r, id;
} arr[MAX_N + 5];
int m_time[MAX_N + 5]; // m_time[i]代表第i台机器结束挤奶的时间
int ans[MAX_N + 5];

bool cmp(const Data &a, const Data &b) {
    if (a.l != b.l) return a.l < b.l;
    return a.id < b.id;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &arr[i].l, &arr[i].r);
        arr[i].id = i;
    }
    sort(arr, arr + n, cmp);
    int count = 0;
    for (int i = 0; i < n; ++i) {
        int pos = -1; // 挤奶机编号
        for (int j = 0; j < count; ++j) {
            if (m_time[j] < arr[i].l) { // 把当前挤奶机分配给奶牛
                pos = j;
                break;
            }
        }
        if (pos == -1) pos = (count++); // 分配一台新的挤奶机
        m_time[pos] = arr[i].r;
        ans[arr[i].id] = pos + 1;
    }
    printf("%d\n", count);
    for (int i = 0; i < n; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}