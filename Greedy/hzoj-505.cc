/*
现在有 n 个正整数，将他们连成一排，组成一个最大的整数。
例如，现在有三个整数 13,312,343，连接成最大整数为 34331213。
输入:
第一行一个整数 n。（1≤n≤100000）
第二行 n 个不超过 int 类型范围的正整数。
输出:
输出一个数表示组成的最大整数。
样例输入:
3
121 12 96
样例输出:
9612121
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 贪心策略，当字典序 A + B > B + A 时，把 A 排在 B 的前面总是全局最优的
bool cmp(const string &a, const string &b) {
    return a + b > b + a;
}

int main() {
    vector<string> arr;
    string s;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        arr.push_back(s);
    }
    sort(arr.begin(), arr.end(), cmp);
    for (int i = 0; i < n; ++i) {
        cout << arr[i];
    }
    cout << endl;
    return 0;
}