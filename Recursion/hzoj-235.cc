/*
递归实现指数型枚举
从 1 ~ n 这 n 个整数中随机选取任意多个，每种方案里的数从小到大排列，按字典序输出所有可能的选择方案。
输入：
​ 输入一个整数 n 。（1 <= n <= 10）
输出：
​ 每行一组方案，每组方案中两个数之间用空格分隔。
​ 注意每行最后一个数后没有空格。
样例输入：
3
样例输出：
1
1 2
1 2 3
1 3
2
2 3
3
*/

#include <iostream>

// 把每个排列看成一个数组
int arr[10];

void print_one_result(int n) {
    for (int i = 0; i <= n; ++i) {
        if (i) std::cout << " ";
        std::cout << arr[i];
    }
    std::cout << std::endl;
    return;
}

// 当前数组位置 i 上最小可填的数是 j ，最大可填的是 n 的情况下，能实现的所有指数型枚举
void gen_enum(int i, int j, int n) {
    // 边界条件：当j > n时，没有枚举了直接返回
    if (j > n) {
        return;
    }
    // 当前位置为j，排列表示为 j + gen_enum(i + 1, j + 1, n)
    // 当前位置为j + 1，排列表示为 j + 1 + gen_enum(i + 1, j + 2, n)
    // 当前位置为j + 2，排列表示为 j + 2 + gen_enum(i + 1, j + 3, n)
    // ...
    // 当前位置为n，排列表示为 n + gen_enum(i + 1, n + 1, n)，直接返回空
    for (int k = j; k <= n; ++k) {
        arr[i] = k;
        print_one_result(i);
        gen_enum(i + 1, k + 1, n);
    }
    return;
}

int main() {
    int n;
    std::cin >> n;
    if (n < 1 || n > 10) {
        return 0;
    }
    gen_enum(0, 1, n);
    return 0;
}