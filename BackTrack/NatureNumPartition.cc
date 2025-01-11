/*
任何一个大于 1 的自然数 n，总可以拆分成若干个小于 n 的自然数之和。
现在给你一个自然数 n，要求你求出 n 的拆分成一些数字的和。
每个拆分后的序列中的数字从小到大排序。然后你需要输出这些序列，其中字典序小的序列需要优先输出。
输入格式: 
待拆分的自然数 n。
输出格式:
若干数的加法式子。
样例输入:
7
样例输出:
1+1+1+1+1+1+1
1+1+1+1+1+2
1+1+1+1+3
1+1+1+2+2
1+1+1+4
1+1+2+3
1+1+5
1+2+2+2
1+2+4
1+3+3
1+6
2+2+3
2+5
3+4
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int ans[20] = {0};

void print_one_result(int n) {
    if (n < 2) {
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (i) cout << "+";
        cout << ans[i];
    }
    cout << endl;
    return;
}

// 参数说明:
// k: 当前拆出来了k个数字
// start_num: 当前拆分的起始数字
// n: 还未被拆分部分的数字大小
void dfs(int k, int start_num, int n) {
    if (n == 0) {
        print_one_result(k);
        return;
    }
    if (start_num > n) return;
    for (int i = start_num; i <= n; ++i) {
        ans[k] = i;
        dfs(k + 1, i, n - i);
    }
    return;
}

int main() {
    int n;
    cin >> n;
    dfs(0, 1, n);
    return 0;
}