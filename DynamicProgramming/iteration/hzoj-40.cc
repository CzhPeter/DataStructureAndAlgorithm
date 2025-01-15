/*
小海是一个顽皮的少年，对于爬楼梯这种事情，他从来都不愿意一步一步走，
每次上楼梯的时候，要么往上跨两级，要么往上跨三级。对于有 n 级台阶的楼梯，
小海想知道他从最下面走到最上面的方法总数。
输入:
输入一个数字 n（1≤n≤500），代表台阶总数。
输出:
输出一个整数，代表小海从最下面走到最上面的方法总数。
样例输入:
5
样例输出:
2
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

// f[n]代表登上n级的方法总数
// 最后一步跨2步: f[n - 2] 
// 最后一步跨3步: f[n - 3]
// 递推公式: f[n] = f[n - 2] + f[n - 3]

#define MAX_N 500
BigInt f[MAX_N + 5];

int main() {
    int n;
    cin >> n;
    f[0] = 1;
    f[1] = 0;
    f[2] = 1;
    for (int i = 3; i <= n; ++i) {
        f[i] = f[i - 2] + f[i - 3];
    }
    cout << f[n] << endl;
    return 0;
}