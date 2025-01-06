#include <iostream>
#include <vector>
#include <deque>

using namespace std;

void output(vector<int> &arr) {
    int n = arr.size(), len = 0;
    for (int i = 0; i < n; ++i) {
        len += printf("%3d", i);
    }
    printf("\n");
    for (int i = 0; i < len; ++i) {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < n; ++i) {
        printf("%3d", arr[i]);
    }
    printf("\n");
    return;
}

// 单调队列：解决区间内最值问题
int main() {
    int n, k;
    cin >> n >> k;
    vector<int> arr;
    deque<int> q;
    for (int i = 0, a; i < n; ++i) {
        cin >> a;
        arr.push_back(a);
    }
    output(arr);
    for (int i = 0; i < n; ++i) {
        // 维护单调递增队列，存储值下标
        while (!q.empty() && arr[q.back()] > arr[i]) {
            q.pop_back();
        }
        q.push_back(i);
        // 滑动窗口移动时，队首出队
        if (i - q.front() == k) {
            q.pop_front();
        }
        printf("[%d, %d] = arr[%d] = %d\n", 
               max(i - k + 1, 0), i, 
               q.front(), arr[q.front()]);
    }
    return 0;
}