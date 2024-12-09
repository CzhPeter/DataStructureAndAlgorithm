/*
超市里有N个商品，第i个商品必须在保质期（第di天）之前卖掉，若卖掉可让超市获得pi的利润。
每天只能卖一个商品，现在你要让超市获得最大的利润
输入
每组数据第一行为一个整数N(0 < N <= 10000)，即超市的商品数目
之后N行，每行各有两个整数，第i行为pi, di(1 <= pi, di <= 10000)
输出
输出当前条件下超市的最大利润
*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Data {
    Data(int p, int d) : p(p), d(d) {}
    int p, d;
    // 排序规则：按过期日期从小到大排序，如果过期日期一样，按利润从大到小排序
    bool operator<(const Data &obj) const {
        if (d != obj.d) return d < obj.d;
        return p > obj.p;
    }
};

typedef pair<int, int> PII;

int main () {
    int n;
    cin >> n;
    vector<Data> arr;
    set<PII> s;
    for (int i = 0, p, d; i < n; ++i) {
        cin >> p >> d;
        arr.push_back(Data(p, d));
    }
    sort(arr.begin(), arr.end());
    for (int i = 0; i < n; ++i) {
        if (arr[i].d > s.size()) {
            s.insert(PII(arr[i].p, i));
        } else {
            if (arr[i].p > s.begin()->first) {
                s.erase(s.begin());
                s.insert(PII(arr[i].p, i));
            }
        }
    }
    int ans = 0;
    for (auto x : s) {
        ans += x.first;
    }
    cout << ans << endl;
    return 0;
}