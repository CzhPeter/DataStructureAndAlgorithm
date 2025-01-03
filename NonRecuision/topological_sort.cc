/*
给定一个有 N 个点，M 条边的有向无权图，现求其拓扑排序。若有多个拓扑排序，则尽可能让小数在前大数在后。
输入：
输入文件第一行是两个整数 n 和 m。接下来 m 行，每行 2 个整数 a,b，表示有一条从 a 点到 b 点的边，保证数据中无环。
输出：
输出文件包含 1 行，共有 N 个整数，表示拓扑排序，每两个数中间用空格隔开。
样例输入：
7 6
1 2
1 4
2 3
4 5
3 6
5 6
样例输出：
1 2 3 4 5 6 7
*/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

#define MAX_N 2000
int indegree[MAX_N + 5] = {0}; // 记录每个节点的入度
vector<vector<int>> g(MAX_N + 5); // g[i]是i节点指向其他节点的编号
int ans[MAX_N + 5];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        indegree[b] += 1; // 更新入度
        g[a].push_back(b); // 存储边
    }
    // 拓扑排序：记录入度为0的节点
    set<int> q; // 模拟优先队列（小顶堆）保证输出时小节点在前
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) {
            q.insert(i);
        }
    }
    int count = 0;
    while (q.size() > 0) {
        int now = *q.begin(); // front() / top()
        ans[count++] = now;
        q.erase(q.begin()); // pop()
        // 处理出队节点指向的节点，使他们入度都减1
        for (int i = 0, I = g[now].size(); i < I; ++i) {
            int t = g[now][i];
            indegree[t] -= 1;
            if (indegree[t] == 0) {
                q.insert(t);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (i) cout << " ";
        cout << ans[i]; 
    }
    cout << endl;
    return 0;
}