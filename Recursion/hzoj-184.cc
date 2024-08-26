/*
https://oj.haizeix.com/problem/184
路飞买了一堆桃子不知道个数，第一天吃了一半的桃子，还不过瘾，又多吃了一个。
以后他每天吃剩下的桃子的一半还多一个，到 n 天只剩下一个桃子了。
路飞想知道一开始买了多少桃子
输入：一个整数 n (2 <= n <= 30)
输出：买的桃子的数量
*/

#include <iostream>

// 能吃n天的桃子数量
int num_to_buy(int days) {
    // 边界条件
    if (days == 2) {
        return (1 + 1) * 2;
    }
    // 用n-1天的桃子数量来计算n天的桃子数量
    return (num_to_buy(days - 1) + 1) * 2;
}

int main() {
    int days;
    std::cin >> days;
    if (days < 2 || days > 30) {
        std::cout << "Wrong input!" << std::endl;
        return 0;
    }
    std::cout << num_to_buy(days) << std::endl;
    return 0;
}