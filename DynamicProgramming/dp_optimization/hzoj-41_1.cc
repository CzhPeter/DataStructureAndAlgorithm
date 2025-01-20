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

// 递推状态重定义: f[n] 代表前 n 块墙壁，首尾颜色不同的方法总数
// 状态转移推导: 
// 倒数第二块墙壁和首块墙壁颜色相同: 此时倒数第三块墙壁和首块颜色一定不同，
// 方案有 f[n - 2] 种，同时尾块墙壁的颜色有 k - 1 种，
// 所以 f[n] = f[n - 2] * (k - 1)
// 倒数第二块墙壁和首块墙壁颜色不同: 方案有 f[n - 1] 种，同时尾块墙壁的颜色有 k - 2 种，
// 所以 f[n] = f[n - 1] * (k - 2)
// 状态转移方程:
// f[n] = f[n - 2] * (k - 1) + f[n - 1] * (k - 2)

#define MAX_N 1000

BigInt f[MAX_N + 5] = {0};

int main() {
    int n, k;
    cin >> n >> k;
    f[1] = k; // 1块墙壁
    f[2] = k * (k - 1); // 2块墙壁颜色不同
    f[3] = k * (k - 1) * (k - 2); // 3块墙壁
    // 因为要看倒数第三块墙壁的情况，所以只能从f[4]开始迭代
    for (int i = 4; i <= n; ++i) {
        f[i] = f[i - 1] * (k - 2) + f[i - 2] * (k - 1);
    }
    cout << f[n] << endl;
    return 0;
}