/*
给出正整数 n，要求按如下方式构造数列：
1. 只有一个数 n 的数列是一个合法的数列。
2. 在一个合法的数列的末尾加入一个正整数，但是这个正整数不能超过该数列最后一项的一半，
可以得到一个新的合法数列。
请你求出，一共有多少个合法的数列。
两个合法数列 a,b 不同当且仅当两数列长度不同或存在一个正整数 i≤∣a∣，使得 ai≠bi 。
输入格式:
输入只有一行一个整数，表示 n。
输出格式:
输出一行一个整数，表示合法的数列个数。
样例输入:
6
样例输出:
6
解释
满足条件的数列为：
6
6,1
6,2
6,3
6,2,1
6,3,1
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// 递推状态: f[i] 代表以 i 数字开头的合法数列的数量
// 容斥原理推导: 合法数列数量 = 不能再向后扩展的数列数量 + 可以向后扩展的数列数量
// 递推公式: f[i] = 1 + (f[i/2] + f[i/2 - 1] + ... + f[1])

#define MAX_N 1000
int f[MAX_N + 5] = {0};

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        f[i] = 1;
        for (int j = 1; j <= i / 2; ++j) {
            f[i] += f[j];
        }
    }
    cout << f[n] << endl;
    return 0;
}