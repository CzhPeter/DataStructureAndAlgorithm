/*
​给定一个矩阵，在其中找一个子矩阵，使得子矩阵中所有元素的和加在一起最大。
输入:
​第一行输入一个整数 N 表示矩阵的大小为 NxN。
接下来 N 行，每行 N 个数，表示矩阵中的元素的值 C。（−128≤C≤127）
输出:
输出一个整数，表示最大子阵和。
样例输入:
4
0 -2 -7 0 
9 2 -6 2 
-4 1 -4 1 
-1 8 0 -2
样例输出:
15
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define MAX_N 100
int arr[MAX_N + 5][MAX_N + 5];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> arr[i][j];
            arr[i][j] += arr[i - 1][j]; // 将矩阵内每个元素替换为其所在列的前缀和
        }
    }
    int ans = INT32_MIN;
    // 以i为起点行，j为终点行去找子矩阵
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            int S = 0; // 记录最大子序和
            for (int k = 1; k <= n; ++k) {
                int a = arr[j][k] - arr[i - 1][k]; // 计算第 i 行到第 j 行的第 k 列元素和
                if (S >= 0) S += a;
                else S = a;
                if (S > ans) ans = S;
            }
        }
    }
    cout << ans << endl;
    return 0;
}