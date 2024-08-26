/*
https://oj.haizeix.com/problem/186
有一个小球掉落在一串连续的弹簧板上，小球落到某一个弹簧板后，
会被弹到某一个地点，直到小球被弹到弹簧板以外的地方。
假设有n个连续的弹簧板，每个弹簧板占一个单位距离，a[i]代表代表第i个弹簧板会把小球向前弹a[i]个距离。
比如位置1的弹簧能让小球前进2个距离到达位置3。
如果小球落到某个弹簧板后，经过一系列弹跳会被弹出弹簧板，那么小球就能从这个弹簧板弹出来。
现在小球掉到了1号弹簧板上面，那么这个小球会被弹起多少次，才会弹出弹簧板。
1号弹簧板也算一次。
输入：
第一个行输入一个 n 代表一共有 n (1 <= n <= 100000) 个弹簧板。
第二行输入 n 个数字，中间用空格分开。
第 i 个数字 a[i] (0 < a[i] <= 30) 代表第 i 个弹簧板可以让小球移动的距离。
输出：一个整数，表示小球被弹起的次数。
*/

#include <iostream>

// 小球从i位置掉落，到弹出弹簧板，需要弹几次
int bounce_times(int pos, int arr[], int n) {
    // 边界条件：落在弹簧板以外的地方，弹起次数为0
    if (pos >= n) {
        return 0;
    }
    return bounce_times(pos + arr[pos], arr, n) + 1;
}

int main() {
    int n;
    std::cin >> n;
    if (n <= 0 || n > 100000) {
        return 0;
    }
    int arr[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
        if (arr[i] <= 0 || arr[i] > 30) {
            return 0;
        }
    }
    std::cout << bounce_times(0, arr, n) << std::endl;
    return 0;
}