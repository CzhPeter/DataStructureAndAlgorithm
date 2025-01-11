/*
一个 n x n 的跳棋棋盘，有 n 个棋子被放置在棋盘上，
使得每行、每列有且只有一个，每条对角线（包括两条主对角线的所有平行线）上至多有一个棋子。
输入格式:
一行一个正整数 n, 表示棋盘是 n x n 大小的。
输出格式:
前三行为前三个解，每个解的两个数字之间用一个空格隔开。第四行只有一个数字，表示解的总数。
解输出方式：根据行的顺序输出列的编号。
样例输入：
6
样例输出：
2 4 6 1 3 5
3 6 2 5 1 4
4 1 5 2 6 3
4
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// 二进制掩码：n位1加上一个0，比如 n = 6 时，得到 1111110
// 掩码含义，二进制对应的位权上是否可以放置皇后，1代表可以放置
#define MASK(n) ((1 << (n + 1)) - 2)

unordered_map<int, int> index_map; // 位权到编号的映射关系
int total_print = 3;
int arr[20];

void print_one_result(int n) {
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << " ";
        cout << arr[i];
    }
    cout << endl;
    total_print -= 1;
    return;
}

// 参数定义：
// i: 正在分配第 i 行的皇后
// t1: 列上可放置的状态；t2: 正斜/行上可放置的状态；t3: 反斜\行上可放置的状态
int dfs(int i, int t1, int t2, int t3, int n) {
    if (i > n) {
        if (total_print) print_one_result(n);
        return 1;
    }
    int ans = 0;
    // 找到列上的最后一位1，即最后一个可放置皇后的列
    for (int t = t1; t; t -= (-t & t)) {
        int j = index_map[-t & t]; // 找到可使用的列编号，此时(i, j)坐标可用
        // 判断斜行是否有冲突，即判断掩码对应位置是否为1
        if ((t2 & (1 << (i + j - 1))) && (t3 & (1 << (i - j + n)))) {
            arr[i] = j; // 记录放置位置
            // 正反斜行都可以使用，继续搜索下一行
            // 传入的参数需要将当前位置的掩码都置为0
            ans += dfs(i + 1, t1 ^ (1 << j), 
                       t2 ^ (1 << (i + j - 1)), 
                       t3 ^ (1 << (i - j + n)), 
                       n);
        }
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    // 初始化位权映射表
    for (int i = 0; i < 2 * n; ++i) {
        index_map[1 << i] = i;
    }
    int ans = dfs(1, MASK(n), MASK(2 * n - 1), MASK(2 * n - 1), n); // 列有n个位置，斜行有2 * n - 1个位置
    cout << ans << endl;
    return 0;
}