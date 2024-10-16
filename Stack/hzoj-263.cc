/*
有 n 列火车按 1 到 n 的顺序从东方左转进站，这个车站是南北方向的，
它虽然无限长，只可惜是一个死胡同，而且站台只有一条股道，火车只能倒着从西方出去，
而且每列火车必须进站，先进后出。
​进站的火车编号顺序为 1∼n，现在请你按火车编号从小到大的顺序，输出前 20 种可能的出站方案。
*/

#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

// 相当于模拟序列的入栈出栈过程
bool isValid(int a[], int n) {
    stack<int> s;
    int x = 1; // 当前可以入栈的最小元素值
    for (int i = 0; i < n; ++i) {
        if (s.empty() || s.top() < a[i]) {
            // 把比序列当前元素小的值全部入栈
            while (x <= a[i]) {
                s.push(x);
                x += 1;
            }
        }
        // 如果当前元素和栈顶元素不一样，说明当前元素的值在栈底，无法弹出，该序列非法
        if (s.empty() || s.top() != a[i]) {
            return false;
        }
        // 如果没有返回，就把当前元素从栈顶弹出
        s.pop();
    }
    return true;
}

int main() {
    int n, a[25];
    int count = 20;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1;
    }
    do {
        if (isValid(a, n)) {
            for (int i = 0; i < n; ++i) {
                cout << a[i];
            }
            cout << endl;
            count -= 1;
        }
    } while (next_permutation(a, a + n) && count);
    return 0;
}