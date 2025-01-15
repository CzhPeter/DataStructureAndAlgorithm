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

// 递推状态: f[n][i][j] 表示n个部分，首块为i色，尾块为j色的方案数
// n 个部分，首块为 i 色，尾块为j色的方案数 = n - 1 个部分，首块为 i 色，尾块不为 j 色方案数之和
// 最后将 f[n][i][j] 种所有 i != j 的方案累加
// 初值推导: 只有一块墙壁，因此只有 i == j 的时候有一种方案
// f[1][i][j] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}

#define MAX_N 1000
#define MAX_K 10

BigInt f[2][MAX_K + 5][MAX_K + 5];

int main() {
    int n, k;
    cin >> n >> k;
    // 初始化一块墙壁的情况
    for (int i = 1; i <= k; ++i) {
        f[1][i][i] = 1;
    }
    for (int wall_size = 2; wall_size <= n; ++wall_size) {
        for (int i = 1; i <= k; ++i) {
            for (int j = 1; j <= k; ++j) {
                f[wall_size % 2][i][j] = 0;
                // 递推公式
                for (int l = 1; l <= k; ++l) {
                    if (l == j) continue;
                    f[wall_size % 2][i][j] += f[(wall_size - 1) % 2][i][l];
                }
            }
        }
    }
    BigInt ans = 0;
    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= k; ++j) {
            if (i == j) continue;
            ans += f[n % 2][i][j];
        }
    }
    cout << ans << endl;
    return 0;
}