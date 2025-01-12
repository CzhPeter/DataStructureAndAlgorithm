/*
公司有 M 个任务需要完成，每个任务有一个难度系数 Yi 并且需要一定的时间 Xi 完成。
现在有 N 台机器，每台机器有最大工作时间和最大工作难度，
只有当机器的最大工作时间和最大工作难度大于等于任务的时间和任务的难度时，机器才能完成这个任务。
每天机器每天只能完成一个任务，一个任务只能被一台机器完成。
当完成一个任务时，公司能获得 500 * Xi + 2 * Yi 的报酬。求今天公司最多能获得的报酬。
输入:
​第一行输入两个整数 N,M。
​接下来 N 行，每行两个数，表示机器的最大工作时间和最大工作难度。
​接下来 M 行，每行两个数，表示任务需要的时间和任务的难度。
输出:
输出一行两个数，第一个数为能完成的最大任务数，第二个数为今天能获取的最高报酬。
样例输入:
1 2
100 3
100 2
100 1
样例输出:
1 50004
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// 贪心策略:
// 由于任务时间的权重远大于难度，且 0<Xi<1400, 0<Yi<=100，明显选Xi大的收益一定更大，
// 将所有任务以及机器按照时间从大到小排序，时间相同的按照任务难度从大到小排序，
// 维护能处理当前任务的所有机器，选择其中难度系数最小的

#define MAX_N 100000

struct Data {
    int x, y;
};
Data task[MAX_N + 5], machine[MAX_N + 5];

bool cmp(const Data &a, const Data &b) {
    if (a.x != b.x) return a.x > b.x;
    return a.y > b.y;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &machine[i].x, &machine[i].y);
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &task[i].x, &task[i].y);
    }
    sort(machine, machine + n, cmp);
    sort(task, task + m, cmp);
    int count[105] = {0}; // count[i]代表难度系数为i的机器有多少台
    long long ans = 0, task_count = 0;
    for (int i = 0, j = 0; i < m; ++i) {
        while (j < n && machine[j].x >= task[i].x) {
            count[machine[j].y] += 1; // 记录能处理当前任务时间的机器，其能处理的难度系数，及难度系数对应的机器数量
            j += 1;
        }
        // 为当前任务选择能处理的难度系数最小的机器
        for (int y = task[i].y; y <= 100; ++y) {
            if (count[y] == 0) continue;
            count[y] -= 1;
            ans += 500 * task[i].x + 2 * task[i].y;
            task_count += 1;
            break; // 选完机器跳出循环，遍历下一个任务
        }
    }
    printf("%d %lld\n", task_count, ans);
    return 0;
}