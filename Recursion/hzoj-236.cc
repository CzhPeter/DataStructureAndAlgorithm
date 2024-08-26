/*
递归实现组合型枚举
从 1 ~ n 这 n 个整数中随机选取 m 个，每种方案里的数从小到大排列，按字典序输出所有可能的选择方案。
输入：
​ 输入一个整数 n 。（1 <= m <= n <= 10）
输出：
​ 每行一组方案，每组方案中两个数之间用空格分隔。
​ 注意每行最后一个数后没有空格。
样例输入：
3 2
样例输出：
1 2
1 3
2 3
*/

#include <iostream>

int arr[10];

void print_one_result(int n) {
    for (int i = 0; i < n; ++i) { // arr[m]未赋值，所以不能是<=
        if (i) std::cout << " ";
        std::cout << arr[i];
    }
    std::cout << std::endl;
    return;
}

// 当前位置 i 取最小可选的值 j ，最大值可选值为 n 时，能生成的枚举
void gen_enum(int i, int j, int n, int m) {
    // 边界条件：最多枚举 m 个位置，当前位置为 m 时，枚举结束
    if (i == m) {
        print_one_result(m);
        return;
    }
    // 当前位置为 j 时， j + f(i + 1, j + 1, n)
    // 当前位置为 j + 1 时， j + 1 + f(i + 1, j + 2, n)
    // ...
    for (int k = j; k <= n && m - i - 1 <= n - k; ++k) { // 剪枝
        // k 不一定能取到 n，需要保证剩下的数够填剩下的位置
        arr[i] = k;
        gen_enum(i + 1, k + 1, n, m);
    }
    return;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    if (n < 1 || n > 10) return -1;
    if (m < 1 || m > n) return -1;
    gen_enum(0, 1, n, m);
    return 0;
}