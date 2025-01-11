/*
呵呵，有一天我做了一个梦，梦见了一种很奇怪的电梯。大楼的每一层楼都可以停电梯，
而且第 i 层楼（1≤i≤N）上有一个数字 Ki（0≤Ki≤N）。
电梯只有四个按钮：开，关，上，下。
上下的层数等于当前楼层上的那个数字。当然，如果不能满足要求，相应的按钮就会失灵。
例如：3,3,1,2,5 代表了 Ki（K1=3，K2=3，……），
从 1 楼开始。在 1 楼，按“上”可以到 4 楼，按“下”是不起作用的，因为没有 −2 楼。
那么，从 A 楼到 B 楼至少要按几次按钮呢？
输入格式：
共二行。
第一行为三个用空格隔开的正整数，表示 N,A,B（1≤N≤200，1≤A,B≤N）。
第二行为 N 个用空格隔开的非负整数，表示 Ki 。
输出格式：
一行，即最少按键次数，若无法到达，则输出 -1。
样例输入：
5 1 5
3 3 1 2 5
样例输出：
3
*/

#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 200
int to[MAX_N + 5];
int dis[MAX_N + 5]; // 存储起点到每个节点的最短距离

// 参数说明：
// k: 到达当前 a 点用了 k 步
// a: 当前点
// b: 终点
// n: 总节点数
void dfs(int k, int a, int n) {
    if (dis[a] <= k) return; // 如果当前到a点所花的步数大于dis[a]，直接停止搜索
    dis[a] = k;
    // 处理电梯上升情况
    if (a + to[a] <= n) {
        dfs(k + 1, a + to[a], n);
    }
    // 处理电梯下降情况
    if (a - to[a] >= 1) {
        dfs(k + 1, a - to[a], n);
    }
    return;
}

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    for (int i = 1; i <= n; ++i) {
        cin >> to[i];
    }
    for (int i = 1; i <= n; ++i) {
        dis[i] = n + 1;
    }
    dfs(0, a, n);
    cout << (dis[b] == n + 1 ? -1 : dis[b]) << endl;
    return 0;
}