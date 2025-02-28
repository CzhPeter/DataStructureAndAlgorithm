/*
一个操作数序列，1,2,…,n，栈 A 的深度大于 n。
现在可以进行两种操作，
将一个数，从操作数序列的头端移到栈的头端（对应数据结构栈的 push 操作）
将一个数，从栈的头端移到输出序列的尾端（对应数据结构栈的 pop 操作）
使用这两种操作，由一个操作数序列就可以得到一系列的输出序列，
你的程序将对给定的 n，计算并输出由操作数序列 1,2,…,n 经过操作可能得到的输出序列的总数。
输入格式:
输入文件只含一个整数 n（1≤n≤18）。
输出格式:
输出文件只有一行，即可能输出序列的总数目。
样例输入:
3
样例输出:
5
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;

// 递推状态: f[n] 表示 n 个出栈序列
// 容斥原理推导: n 个出栈序列 = 出栈序列最后一个元素为1的方案数 + 出栈序列最后一个元素为2的方案数 + ... + 出栈序列最后一个元素为n的方案数
// 设最后一个出栈数字是 x 的情况下，方案数怎么求？
// x 在入栈之前，所有小于 x 的值必须入栈出栈，x 入栈之后，所有大于 x 的值必须入栈出栈，最后 x 出栈
// 所有小于 x 的值(x - 1个)的出栈序列方案数为: f[x - 1], 所有大于 x 的值(n - x个)的出栈序列方案数为 f[n - x]
// 递推公式: f[x] = f[x - 1] * f[n - x]

#define MAX_N 18
int f[MAX_N + 5];

int main() {
    int n;
    cin >> n;
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        f[i] = 0;
        for (int x = 1; x <= i; ++x) {
            f[i] += f[x - 1] * f[i - x];
        }
    }
    cout << f[n] << endl;
    return 0;
}