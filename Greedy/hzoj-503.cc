/*
一群人去旅行，要租用独木舟，每艘独木舟最多乘两人，且所有独木舟有一个统一的载重限度。
给出独木舟的载重限度和每个人的体重，现求最少需要租用多少独木舟。
输入:
​第一行一个整数 w，表示独木舟的载重量。（80≤w≤200）
第二行一个整数 n，表示旅游人数。 （1≤n≤30000）
接下来 n 行，每行一个数表示 ai，即每个人的重量 （5≤ai≤w）
输出:
​输出一个数表示最少需要的独木舟数量。
样例输入:
100
9
90
20
20
30
50
60
70
80
90
样例输出:
6
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 贪心策略：最重的人和最轻的人能坐就坐一条船，否则最重的人自己坐一条船
int main() {
    int w, n;
    cin >> w >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    int i = 0, j = n - 1;
    int count = 0;
    while (i < j) {
        if (arr[i] + arr[j] <= w) {
            i++;
            j--;
        } else {
            j--;
        }
        count += 1;
    }
    if (i == j) count += 1;
    cout << count << endl;
    return 0;
}