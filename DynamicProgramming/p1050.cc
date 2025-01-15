/*
众所周知，2 的正整数次幂最后一位数总是不断的在重复 2,4,8,6,2,4,8,6… 
我们说 2 的正整数次幂最后一位的循环长度是 4（实际上 4 的倍数都可以说是循环长度，但我们只考虑最小的循环长度）。
类似的，其余的数字的正整数次幂最后一位数也有类似的循环现象。
这时问题就出来了：是不是只有最后一位才有这样的循环呢？对于一个整数 n 的正整数次幂来说，
它的后 k 位是否会发生循环？如果循环的话，循环长度是多少呢？
注意：
如果 n 的某个正整数次幂的位数不足 k，那么不足的高位看做是 0。
如果循环长度是 L，那么说明对于任意的正整数 a，n 的 a 次幂和 a+L 次幂的最后 k 位都相同。
输入格式:
共一行，包含两个整数 n 和 k。n 和 k 之间用一个空格隔开，表示要求 n 的正整数次幂的最后 k 位的循环长度。
输出格式:
一个整数，表示循环长度。如果循环不存在，输出 −1。
样例输入:
32 2
样例输出:
4
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

// 打表查看循环节
void check(int n, int k) {
    int base = 1;
    for (int i = 0; i < k; ++i, base *= 10); // base = 10 ^ k，帮助取得n的最后k位
    int x = n % base;
    int y = x;
    int cnt = 1;
    while (x * y % base != x) { // 模拟 n 的 m 次方时末尾 k 位的情况，末尾 k 位等于 x 时停止
        cout << "y = " << y << "(" << cnt << "), ";
        y = y * x % base;
        if (cnt % 4 == 0) cout << endl;
        cnt += 1;
    }
    cout << cnt << endl;
}

class BigInt : public vector<int> {
public:
    BigInt() { push_back(0); }

    BigInt(int n, int v) : vector<int>(n, v) {}

    BigInt(int x) {
        push_back(x);
        process_digit();
        return;
    }

    BigInt(string &s, int k) {
        for (int i = 0, j = s.size() - 1; i < k; ++i, --j) {
            push_back(s[j] - '0');
        }
        return;
    }

    BigInt &operator *= (int x) {
        for (int i = 0; i < size(); ++i) {
            at(i) *= x;
        }
        process_digit();
        return *this;
    }

    BigInt operator*(const BigInt &a) {
        BigInt ret(min(MaxLen, int(size() + a.size() - 1)), 0);
        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < a.size(); ++j) {
                if (i + j >= MaxLen) continue;
                ret[i + j] += at(i) * a[j];
            }
        }
        ret.process_digit();
        return ret;
    }

    static int MaxLen;

private:
    void process_digit() {
        for (int i = 0; i < size(); ++i) {
            if (at(i) < 10) continue;
            if (i + 1 < MaxLen) {
                if (i + 1 == size()) push_back(0);
                at(i + 1) += at(i) / 10;
            }
            at(i) %= 10;
        }
        return;
    }
};

int BigInt::MaxLen = 0;

ostream &operator<<(ostream &out, const BigInt &a) {
    for (int i = a.size() - 1; i >= 0; --i) {
        out << a[i];
    }
    return out;
}

int main() {
    string s;
    int k;
    cin >> s >> k;
    BigInt::MaxLen = k;
    BigInt n(s, k);
    BigInt pre_y = n, y; // pre_y: 已知的循环节基数
    vector<int> arr;
    // 按位去确定 n 每一位的循环节长度
    for (int i = 0; i < n.size(); ++i) {
        y = pre_y;
        int cnt = 1;
        while ((y * n).at(i) != n[i]) {
            y  = y * pre_y;
            cnt += 1;
            if (cnt == 11) break; // 不存在循环节的情况
        }
        if (cnt == 11) {
            cout << "-1" << endl;
            return 0;
        }
        arr.push_back(cnt);
        pre_y = y;
    }
    BigInt ans = 1;
    for (int i = 0; i < arr.size(); ++i) {
        ans *= arr[i];
    }
    cout << ans << endl;
    return 0;
}