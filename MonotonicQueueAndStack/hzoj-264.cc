/*
给定从左到右多个矩形，已知这此矩形的宽度都为 1，长度不完全相等。
这些矩形相连排成一排，求在这些矩形包括的范围内能得到的面积最大的矩形，打印出该面积。
所求矩形可以横跨多个矩形，但不能超出原有矩形所确定的范围。
输入:
​输入共两行，第一个数表示矩形的个数 N。接下来 N 个数表示矩形的大小。（1≤N≤100000）
输出:​
输出最大矩形面积。
样例输入:
7
2 1 4 5 1 3 3
样例输出:
8
*/

#include <iostream>
#include <vector>
#include <deque>
#include <stack>

using namespace std;

// 最大矩形的高度 = 某块木板的高度（木板=宽度为1的每个小矩形）
// 最大矩形两侧的木板高度一定小于最大矩形的高度
// 求某块木板对应的最大矩形：分别找到其左右两侧第一个比它高度低的木板
int main() {
    long long n;
    cin >> n;
    vector<long long> arr(n + 2, -1), l(n + 2), r(n + 2); // l, r分别为左/右第一块小于第i块木板的下标
    for (long long i = 1; i <= n; ++i) {
        cin >> arr[i];
    }
    stack<long long> s;
    // 从左往右找右边第一个比arr[i]小的
    for (long long i = 1; i <= n; ++i) {
        while (!s.empty() && arr[i] < arr[s.top()]) {
            r[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    while (!s.empty()) s.pop();
    // 从右往左找左边第一个比arr[i]小的
    for (long long i = n; i >= 0; --i) {
        while (!s.empty() && arr[i] < arr[s.top()]) {
            l[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    long long ans = 0;
    for (long long i = 1; i <= n; ++i) {
        long long height = arr[i], width = r[i] - l[i] - 1;
        ans = max(height * width, ans);
    }
    cout << ans << endl;
    return 0;
}