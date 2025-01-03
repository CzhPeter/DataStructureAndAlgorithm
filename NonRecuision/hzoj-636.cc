/*
小明要去一个国家旅游。这个国家有 N 个城市，编号为 1 至 N，并且有 M 条道路连接着，
小明准备从其中一个城市出发，并只往东走到城市 i 停止。
​所以他就需要选择最先到达的城市，并制定一条路线以城市 i 为终点，使得线路上除了第一个城市，
每个城市都在路线前一个城市东面，并且满足这个前提下还希望游览的城市尽量多。
现在，你只知道每一条道路所连接的两个城市的相对位置关系，但并不知道所有城市具体的位置。
现在对于所有的 i，都需要你为小明制定一条路线，并求出以城市 i 为终点最多能够游览多少个城市。
输入:
​第 1 行为两个正整数 N,M。​ 接下来 M 行，每行两个正整数 x,y，表示了有一条连接城市 x 与城市 y 的道路，
保证了城市 x 在城市 y 西面。
输出:
​N 行，第 i 行包含一个正整数，表示以第 i 个城市为终点最多能游览多少个城市。
样例输入：
5 6
1 2
1 3
2 3
2 4
3 4
2 5
样例输出：
1
2
3
4
3
*/

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

#define MAX_N 100000
int indegree[MAX_N + 5] = {0};
vector<vector<int>> g(MAX_N + 5);
int ans[MAX_N + 5] = {0};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0, x, y; i < m; ++i) {
        scanf("%d%d", &x, &y);
        indegree[y] += 1;
        g[x].push_back(y);
    }
    // 存储入度为0的城市并初始化结果数组
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (indegree[i]) continue;
        q.push(i);
        ans[i] = 1;
    }
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = 0, I = g[now].size(); i < I; ++i) {
            // 求每个城市作为终点时的经过城市最大数量
            int t = g[now][i];
            indegree[t] -= 1;
            if (indegree[t] == 0) {
                q.push(t);
            }
            ans[t] = max(ans[now] + 1, ans[t]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}