/*
给出一个长度为 N 的数组，一个长为 K 的滑动窗口从最左移动到最右，每次窗口移动。
找出窗口在各个位置时的极大值和极小值。
输入：
​第一行两个数 N,K。第二行有 N 个数，表示数组中的元素。
输出：
​输出两行，第一行为窗口在各个位置时的极小值，第二行为窗口在各个位置时的极大值。
样例输入：
8 3
1 3 -1 -3 5 3 6 7
样例输出：
-1 -3 -3 -3 3 3
3 3 5 5 6 7
*/

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    deque<int> q;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    // 单调递增队列维护区间最小值
    for (int i = 0; i < n; ++i) {
        while (!q.empty() && arr[q.back()] > arr[i]) {
            q.pop_back();
        }
        q.push_back(i);
        if (i - q.front() == k) q.pop_front();
        if (i + 1 < k) continue;
        if (i >= k) cout << " ";
        cout << arr[q.front()];
    }
    cout << endl;
    q.clear();
    // 单调递减队列维护区间最大值
    for (int i = 0; i < n; ++i) {
        while (!q.empty() && arr[q.back()] < arr[i]) {
            q.pop_back();
        }
        q.push_back(i);
        if (i - q.front() == k) q.pop_front();
        if (i + 1 < k) continue;
        if (i >= k) cout << " ";
        cout << arr[q.front()];
    }
    cout << endl;
    return 0;
}

