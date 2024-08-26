/*
递归实现排列型枚举
从 1 ~ n 这 n 个整数排成一排并打乱次序，按字典序输出所有可能的选择方案。
输入：
​ 输入一个整数 n 。（1 <= n <= 8）
输出：
​ 每行一组方案，每组方案中两个数之间用空格分隔。
​ 注意每行最后一个数后没有空格。
样例输入：
3
样例输出：
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
*/

#include <iostream>

int arr[8];
int vis[9] = {0}; // 标记用过的数字

void print_one_result(int n) {
    for (int i = 0; i < n; ++i) {
        if (i) std::cout << " ";
        std::cout << arr[i];
    }
    std::cout << std::endl;
    return;
}

// 从当前位置 i 开始，枚举 n 位全排列，并更新用过的数字
void gen_enum(int i, int n) {
    // 边界条件：当前位置为 n 时，说明枚举已经结束
    if (i == n) {
        print_one_result(n);
        return;
    }
    // 最小的未使用过的数字 v[0] + f(i + 1, n)
    // 次小的未使用过的数字 v[1] + f(i + 1, n)
    // ...
    for (int k = 1; k <= n; ++k) { // 全排列：每个位置都可以从1开始取
        if (vis[k]) continue;
        arr[i] = k;
        vis[k] = 1;
        gen_enum(i + 1, n);
        vis[k] = 0; // 走到这行，说明当前位置为k的全排列已经枚举完毕，回收标记
    }
    return;
}

int main() {
    int n;
    std::cin >> n;
    if (n < 1 || n > 8) return -1;
    gen_enum(0, n);
    return 0;
}