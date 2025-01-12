/*
给出两个整数 a,b，每次操作可以把 a 变成 a+1 或 axk 。
求把 a 变成 b 至少需要几步操作。
输入:
​第一行三个数 a,b,k。（0≤a,b,k≤10^18）
输出​:
输出最少操作次数。
样例输入:
2 10 2
样例输出:
3
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 贪心策略: 
// 使用乘 k 操作，优先于 +1 操作 （对应情况1）
// 使用 +1 时，当 a 为 b 的数字前缀，再使用乘 k 操作 （对应情况2）
// ans代表最少操作次数，ans更新策略如下:
// 情况1: 若 a * k <= b, ans += 1 + b % k, b /= k
// 情况2: 若 a * k > b, ans += (b - a), 终止
int main() {
    long long a, b, k, ans = 0;
    cin >> a >> b >> k;
    if (k == 1) {
        cout << b - a << endl;
        return 0;
    }
    if (k == 0) {
        if (b != 0) {
            cout << b - a << endl;
        } else {
            cout << !!(a) << endl;
        }
        return 0;
    }
    while (1) {
        if (a * k <= b) {
            ans += 1 + b % k;
            b /= k;
        } else {
            ans += (b - a);
            break;
        }
    }
    cout << ans << endl;
    return 0;
}