#include <iostream>

// n的阶乘的结果函数
int factorial(int n) {
    // 边界条件
    if (n == 1) {
        return 1;
    }
    // 利用f(n - 1)的值，计算f(n)的值
    return factorial(n - 1) * n;
}

int main() {
    int n;
    std::cin >> n;
    std::cout << factorial(n) << std::endl;
    return 0;
}