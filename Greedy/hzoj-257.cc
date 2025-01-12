/*
有一棵树，它的所有节点都需要染色，每个节点都有一个代价基础值 Ci。
第一个染色的是根节点，其余节点染色的时候其父节点必须已染色。
染色一个节点会用掉一个时间单位，每个节点染色的代价是染完此节点时的总时间 T 乘上这个节点的基础值 Ci。
求染完所有节点所需的最小代价。
输入:
​第一行包含两个整数 N,R 其中，N 是树中节点个数，R 是根节点编号。
​第二行输入 N 个整数，编号为 i 的节点的代价基础值 Ci。（1≤Ci≤500）
​接下来 N−1 行为边的信息，每行两个数分别表示父节点编号和子节点编号。
输出:
​输出一个整数，表示最小代价。
样例输入
5 1
1 2 1 2 4
1 2
1 3
2 4
3 5
样例输出
33
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// 贪心策略:
// 最小代价的染色顺序:
// 1、如果x时最大值节点，一旦其父节点被染色了，下一个染色的一定是x节点
// 2、如果一个节点和其孩子的平均值比它的兄弟节点大的话，该节点比其兄弟节点先染色
// 把最小代价子树合并成一个节点，不断合并后最终成为一个节点

#define MAX_N 1000

int C[MAX_N + 5] = {0}; // C[i]表示第i个节点的权值
int father[MAX_N + 5]; // father[i]表示第i个节点的父节点的编号
int vis[MAX_N + 5] = {0}; // vis[i] = 1表示第i个节点已经被合并过了
int cnt[MAX_N + 5] = {0}; // cnt[i]表示第i个节点下包含的节点数量
double avr[MAX_N + 5] = {0.}; // 对外所比较使用的平均值
int n, r;
int ans = 0;

// 返回最大权值的节点编号
int find_x() {
    int x = -1;
    for (int i = 1; i <= n; ++i) {
        if (i == r || vis[i] == 1) continue;
        if (x == -1 || avr[x] < avr[i]) {
            x = i;
        }
    }
    return x;
}

// 找到x的第一个没有被合并过的父节点
int find_father(int x) {
    if (vis[father[x]]) {
        return find_father(father[x]);
    }
    return father[x];
}

int main() {
    cin >> n >> r;
    for (int i = 1; i <= n; ++i) {
        cin >> C[i];
        ans += C[i]; // 节点全部合并后的权值，为所有节点的权值和
        father[i] = i; // 最后根节点的father[i]会指向自己
        avr[i] = C[i];
        cnt[i] = 1;
    }
    for (int i = 1, a, b; i < n; ++i) {
        cin >> a >> b;
        father[b] = a;
    }
    // 节点合并：每次找到最大值节点，再将其与父节点合并
    for (int i = 1; i < n; ++i) {
        int x = find_x();
        int father_x = find_father(x);
        ans += cnt[father_x] * C[x]; // 更新合并产生的代价
        // 合并
        C[father_x] += C[x];
        cnt[father_x] += cnt[x];
        avr[father_x] = 1.0 * C[father_x] / cnt[father_x];
        vis[x] = 1;
    }
    cout << ans << endl;
    return 0;
}