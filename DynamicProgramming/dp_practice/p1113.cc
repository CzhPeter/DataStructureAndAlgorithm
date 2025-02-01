/*
John 的农场在给奶牛挤奶前有很多杂务要完成，每一项杂务都需要一定的时间来完成它。
比如：他们要将奶牛集合起来，将他们赶进牛棚，为奶牛清洗乳房以及一些其它工作。
尽早将所有杂务完成是必要的，因为这样才有更多时间挤出更多的牛奶。
当然，有些杂务必须在另一些杂务完成的情况下才能进行。
比如：只有将奶牛赶进牛棚才能开始为它清洗乳房，还有在未给奶牛清洗乳房之前不能挤奶。
我们把这些工作称为完成本项工作的准备工作。至少有一项杂务不要求有准备工作，
这个可以最早着手完成的工作，标记为杂务 1。
John 有需要完成的 n 个杂务的清单，并且这份清单是有一定顺序的，
杂务 k (k>1) 的准备工作只可能在杂务 1 至 k−1 中。
写一个程序依次读入每个杂务的工作说明。计算出所有杂务都被完成的最短时间。
当然互相没有关系的杂务可以同时工作，并且，你可以假定 John 的农场有足够多的工人来同时完成任意多项任务。
输入格式:
第1行：一个整数 n (3≤n≤10,000)，必须完成的杂务的数目；
第 2 至 n+1 行，每行有一些用空格隔开的整数，分别表示：
工作序号（保证在输入文件中是从 1 到 n 有序递增的）；完成工作所需要的时间 len (1≤len≤100)；一些必须完成的准备工作，总数不超过 100 个，由一个数字 0 结束。
有些杂务没有需要准备的工作只描述一个单独的 0。
保证整个输入文件中不会出现多余的空格。
输出格式:
一个整数，表示完成所有杂务所需的最短时间。
样例输入:
7
1 5 0
2 2 1 0
3 3 2 0
4 6 1 0
5 1 2 4 0
6 8 2 4 0
7 4 3 5 6 0
样例输出:
23
*/

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

// 问题等价: 先完成准备工作再完成后续 = 拓扑序，用拓扑序去确定每一个任务的最早完成时间
// 这里拓扑序不用额外处理，因为输入顺序就是按拓扑序输入的
// dp状态: dp[i] 代表第 i 个任务的最早完成时间
// 状态转移方程: dp[i] = max(dp[j]) + time[i]
// 即第 i 个任务的所有前置任务的最早完成时间中的最晚时间，再加 i 本身需要的时间
// 最后选择 dp 值中最大的那个，即为所有任务都完成的最早时间

#define MAX_N 10000
int dp[MAX_N + 5];

int main() {
    int n, ans = 0;
    cin >> n;
    for (int i = 1, t, j; i <= n; ++i) {
        cin >> t >> t;
        dp[i] = t;
        while (cin >> j) {
            if (j == 0) break;
            dp[i] = max(dp[i], dp[j] + t);
        }
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}