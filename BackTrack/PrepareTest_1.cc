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
#include <unordered_map>

using namespace std;

#define MAX_N 20
#define MAX_NUM 9999999
int s[10] = {0}, sum[10] = {0};
int t[10][MAX_N + 5]; // t[i][j]表示第i个习题集中第j题需要花费的时间
unordered_map<int, int> index_map; // 位权和题目编号的映射

int solve(int k) {
    int ans = MAX_NUM;
    int T = (1 << s[k]); // 共有2^s[k]种分配方案
    // 遍历每一种分配方案
    for (int i = 0; i < T; ++i) {
        int j = i, l = 0, r = 0;
        // 从后往前遍历题目分配给左脑
        while (j) {
            l += t[k][index_map[j & -j]];
            j -= (j & -j);
        }
        r = sum[k] - l;
        ans = min(ans, max(l, r));
    }
    return ans;
}

int main() {
    for (int i = 0; i < 4; ++i) {
        cin >> s[i]; // 读入每个习题集的题目数量
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < s[i]; ++j) {
            cin >> t[i][j]; // 读入每题需要花费的时间
            sum[i] += t[i][j]; // 计算第i科所有题目所需时间总和
        }
    }
    for (int k = 1, i = 0; i <= MAX_N; ++i, k *= 2) {
        index_map[k] = i;
    }
    int total = 0;
    for (int i = 0; i < 4; ++i) {
        total += solve(i);
    }
    cout << total << endl;
    return 0;
}