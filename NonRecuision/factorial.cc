#include <iostream>
#include <stack>

using namespace std;

int f(int n) {
    if (n == 1) return 1;
    return n * f(n - 1);
}

// 模拟栈内的数据
struct Data {
    Data(int n, int *pre_ret) : n(n), pre_ret(pre_ret) {
        code = 0;
    }
    int n;
    int code, ret, *pre_ret; // pre_ret指向栈下一层的ret变量
};

int non_f(int n) {
    stack<Data> s;
    int ans;
    Data d(n, &ans);
    s.push(d);
    while (!s.empty()) {
        Data &cur = s.top();
        Data pre(cur.n - 1, &(cur.ret));
        switch (cur.code) {
        case 0:
            if (cur.n == 1) {
                *(cur.pre_ret) = 1;
                s.pop();
            } else {
                cur.code = 1;
            }
            break;
        case 1:
            cur.code = 2;
            s.push(pre);
            break;
        case 2:
            // n * f(n - 1)
            *(cur.pre_ret) = cur.n * cur.ret;
            s.pop();
            break;
        }
    }
    return ans;
}

int main() {
    int n; 
    while (cin >> n) {
        cout << f(n) << endl;
        cout << non_f(n) << endl;
    }
    return 0;
}