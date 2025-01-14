/*
如果有一对小兔，每一个月都生下一对小兔，而所生下的每一对小兔在出生后的第三个月也都生下一对小兔。
那么，由一对兔子开始，n 个月后有多少对小兔子呢？
输入:
输入一个数字 n（1≤n≤100），代表题目中询问的月份。
输出:
对于每个询问，输出一行整数，代表 n 月的时候，小兔子的数量。
样例输入:
65
样例输出:
27777890035288
*/

// 递推过程:
//   月份     成年兔子     幼年兔子    兔子总数
// 第一个月       1          0          1
// 第二个月       1          1          2
// 第三个月       2          1          3
// 第四个月       3          2          5
// 第五个月       5          3          8
// 当月成年兔子的数量 = 上一个月的兔子总数
// 当月幼年兔子的数量 = 上上个月的兔子总数
// f(n) = f(n - 1) + f(n - 2), f(1) = 1, f(2) = 2

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

#define MAX_N 100

// 递归超时写法: 太多重复计算
long long f(int n) {
    if (n <= 2) return n;
    return f(n - 1) + f(n - 2);
}

// 递归加记忆化
long long arr[MAX_N + 5] = {0};
long long f1(int n) {
    if (n <= 2) return n;
    if (arr[n]) return arr[n];
    arr[n] = f(n - 1) + f(n - 2);
    return arr[n];
}

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

// 改变求解方向 从f(1)求解到f(n)
BigInt func[MAX_N + 5] = {0};
BigInt f2(int n) {
    func[1] = 1;
    func[2] = 2;
    for (int i = 3; i <= n; ++i) {
        func[i] = func[i - 1] + func[i - 2];
    }
    return func[n];
}

ostream &operator<<(ostream &out, const BigInt &a) {
    for (int i = a.size() - 1; i >= 0; --i) {
        out << a[i];
    }
    return out;
}

int main() {
    int n;
    cin >> n;
    // cout << f(n) << endl;
    // cout << f1(n) << endl;
    cout << f2(n) << endl;
    return 0;
}