/*
给定 A、B、C 三根足够长的细柱，在 A 柱上放有 2n 个中间有孔的圆盘，
共有 n 个不同的尺寸，每个尺寸都有两个相同的圆盘，注意这两个圆盘是不加区分的。
现要将这些圆盘移到 C 柱上，在移动过程中可放在 B 柱上暂存。要求：
1. 每次只能移动一个圆盘；
2. A、B、C 三根细柱上的圆盘都要保持上小下大的顺序。
任务：设 An 为 2n 个圆盘完成上述任务所需的最少移动次数，对于输入的 n，输出 An。
输入格式:
一个正整数 n，表示在 A 柱上放有 2n 个圆盘。
输出格式:
一个正整数, 为完成上述任务所需的最少移动次数 An。
样例输入:
2
样例输出:
6
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

// 递推状态: f[n]: 2n 个盘子 A -> C 的步数
// 容斥原理推导: 先把 2(n - 1) 个盘子 A -> B，再把剩下两个最大的盘子 A -> C，最后 B -> C
// 递推公式: f[n] = f[n - 1] + 2 + f[n - 1] = 2 * f[n - 1] + 2

#define MAX_N 200

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
            if (at(i) < 10) continue;
            if (i == size() - 1) push_back(0);
            at(i + 1) += at(i) / 10;
            at(i) %= 10;
        }
        return;
    }
};

ostream &operator<<(ostream &out, const BigInt &a) {
    for (int i = a.size() - 1; i >= 0; --i) {
        out << a[i];
    }
    return out;
}

BigInt f[MAX_N + 5];

int main() {
    int n;
    cin >> n;
    f[1] = 2;
    for (int i = 2; i <= n; ++i) {
        f[i] = f[i - 1] * 2 + 2;
    }
    cout << f[n] << endl;
    return 0;
}