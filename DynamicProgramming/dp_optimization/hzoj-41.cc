/*
给一个环形的墙壁涂颜色，颜色一共有 k 种，墙壁被竖直地划分成 n 个部分，相邻的部分颜色不能相同。
请你写程序计算出一共有多少种给墙壁上色的方案？
例如，当 n = 5, k = 3 时，下面是一种合法的涂色方案:
蓝 红 黄 红 黄
而由于墙壁是环形的，所以下面就是一种非法的方案:
蓝 红 黄 红 蓝
输入:
输入两个数字 n，k（1≤n≤103，2≤k≤10），分别代表墙壁数量和颜色种类。
输出:
对于每个询问，输出一行整数，合法的墙壁涂色方案数。
样例输入:
5 3
样例输出:
30
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// 大整数解决方案
class BigInt : public vector<int> {
public:
    BigInt() { push_back(0); }

    BigInt(int x) {
        this->push_back(x);
        process_digit();
    }

    BigInt operator+=(const BigInt &a) {
        for (int i = 0; i < a.size(); ++i) {
            if (i >= size()) {
                push_back(a[i]);
            } else {
                at(i) += a[i];
            }
        }
        process_digit();
        return *this;
    }

    BigInt operator+(const BigInt &a) {
        BigInt ret(*this);
        ret += a;
        return ret;
    }

    BigInt &operator *=(int x) {
        for (int i = 0; i < size(); ++i) {
            at(i) *= x;
        }
        process_digit();
        return *this;
    }

    BigInt operator*(int x) {
        BigInt ret(*this);
        ret *= x;
        return ret;
    }

    void process_digit() {
        for (int i = 0; i < size(); ++i) {
            if (at(i) < 100000) continue;
            if (i == size() - 1) push_back(0);
            at(i + 1) += at(i) / 100000;
            at(i) %= 100000;
        }
        return;
    }
};

ostream &operator<<(ostream &out, const BigInt &a) {
    out << a[a.size() - 1];
    for (int i = int(a.size()) - 2; i >= 0; --i) {
        int num = a[i];
        for (int j = 10000; j > 0; j /= 10) {
            out << a[i] % (j * 10) / j;
        }
    }
    return out;
}

// 递推状态重定义: 
// f[n][j] 代表前n块墙壁，在不考虑头尾成环的前提下，第1块涂颜色为0，第n块图颜色j的方法总数
// 状态定义推导: 
// 第1块墙不论是哪种颜色，首块为该颜色的方案是一样多的，
// 因此只要求得一种颜色作为首块的方案数，再乘以颜色的种类数，就可以得到所有方案数
// 状态转移方程:
// f[n][j] = f[n - 1][k]之和(k != j)

#define MAX_N 1000
#define MAX_K 10

BigInt f[MAX_N + 5][MAX_K + 5] = {0};

int main() {
    int n, k;
    cin >> n >> k;
    f[1][0] = 1; // 初始化: 一块墙壁的固定颜色方案数为1
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j < k; ++j) {
            for (int c = 0; c < k; c++) {
                if (c == j) continue;
                f[i][j] += f[i - 1][c]; // 累加倒数第二块墙壁不为j颜色的所有方案
            }
        }
    }
    // 累加末尾墙壁颜色非0的所有方案
    BigInt sum = 0;
    for (int i = 1; i < k; ++i) {
        sum += f[n][i];
    }
    // 乘以第一块墙壁的颜色数
    cout << sum * k << endl;
    return 0;
}