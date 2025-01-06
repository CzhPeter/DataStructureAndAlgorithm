/*
输入一个长度为 n 的整数序列，从中找出一段不超过 M 的连续子序列，使得整个序列的和最大。
​例如: 1,−3,5,1,−2,3: ​当 m=4 时, S=5+1−2+3=7; 当 m=2 或 m=3 时, S=5+1=6。
输入:
第一行两个数 n,m。第二行有 n 个数，要求在 n 个数找到最大子序和。
输出:
​一个数，数出他们的最大子序和。
样例输入:
6 4
1 -3 5 1 -2 3
样例输出:
7
*/

#include <iostream>
#include <vector>
#include <deque>
#include <stack>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> s(n + 1);
    deque<int> q;
    // 形成前缀和序列
    s.push_back(0);
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        s[i] += s[i - 1];
    }
    // 子序列和sum[i:j] = s[j] - s[i - 1]，同时保证 j - i + 1 <= m
    // 使用单调队列维护前缀和的最小值，即s[i - 1]最小时，子序列和最大
    q.push_back(0);
    int ans = INT_MIN;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, s[i] - s[q.front()]);
        while (!q.empty() && s[i] < s[q.back()]) {
            q.pop_back();
        }
        q.push_back(i);
        if (q.front() == i - m) {
            q.pop_front();
        }
    }
    cout << ans << endl;
    return 0;
}