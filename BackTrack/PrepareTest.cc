/*
这次期末考试，kkksc03 需要考 4 科。因此要开始刷习题集，每科都有一个习题集，分别有 s1,s2,s3,s4道题目，
完成每道题目需要一些时间，可能不等（A1,A2,…,As1，B1,B2,…,Bs2，C1,C2,…,Cs3，D1,D2,…,Ds4）。
kkksc03 有一个能力，他的左右两个大脑可以同时计算 2 道不同的题目，但是仅限于同一科。
因此，kkksc03 必须一科一科的复习。
由于 kkksc03 还急着去处理洛谷的 bug，因此他希望尽快把事情做完，所以他希望知道能够完成复习的最短时间。
输入格式:
本题包含 5 行数据：第 1 行，为四个正整数 s1,s2,s3,s4。
第 2 行，为 A1,A2,…,As1 共 s1 个数，表示第一科习题集每道题目所消耗的时间。
第 3 行，为 B1,B2,…,Bs2 共 s2 个数。
第 4 行，为 C1,C2,…,Cs3 共 s3 个数。
第 5 行，为 D1,D2,…,Ds4 共 s4 个数，意思均同上。
输出格式:
输出一行,为复习完毕最短时间。
样例输入:
1 2 1 3		
5
4 3
6
2 4 3
样例输出:
20
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define MAX_N 20
#define MAX_NUM 9999999
int s[10] = {0};
int t[10][MAX_N + 5]; // t[i][j]表示第i个习题集中第j题需要花费的时间
int ans = 0;

// 参数说明:
// k: 当前要做习题的编号
// x: 正在做的习题集编号
// l: 左脑做题总时间
// r: 右脑做题总时间
void dfs(int k, int x, int l, int r) {
    if (k == s[x]) {
        ans = min(ans, max(l, r));
        return;
    }
    // 交给左脑做
    l += t[x][k];
    dfs(k + 1, x, l, r);
    l -= t[x][k];
    // 交给右脑做
    r += t[x][k];
    dfs(k + 1, x, l, r);
    r -= t[x][k];
    return;
}

int main() {
    for (int i = 0; i < 4; ++i) {
        cin >> s[i]; // 读入每个习题集的题目数量
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < s[i]; ++j) {
            cin >> t[i][j]; // 读入每题需要花费的时间
        }
    }
    int total = 0;
    for (int i = 0; i < 4; ++i) {
        ans = MAX_NUM;
        dfs(0, i, 0, 0);
        total += ans;
    }
    cout << total << endl;
    return 0;
}