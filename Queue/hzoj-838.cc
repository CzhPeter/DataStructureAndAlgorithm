/*
定义三元组（a, b, c）（a,b,c 均为正数）的距离 D=|a-b|+|b-c|+|c-a|。
给定 3 个非空整数集合 S1, S2 ,S3, 按升序分别存储在 3 个数组中。
请设计一个尽可能高效的算法，计算并输出所有可能的三元组（a, b, c）（a∈S1,b∈S2,c∈S3）中的最小距离。
例如 S1={-1, 0, 9}, S2={-25，-10，10，11}，S3={2，9，17，30，41}，则最小距离为 2，相应的三元组为（9，10，9）。
输入：
  输入三个参数，分别为存储三个非空集合的队列
输出：
  返回一个整形值，表示所有可能的三元组（a, b, c）（a∈S1,b∈S2,c∈S3）中的最小距离
*/

#include <iostream>
#include <cstdlib>
#include <queue>
using namespace std;

int min_num(int a, int b, int c) {
    if (a > b) swap(a, b);
    if (a > c) swap(a, c);
    return a;
}

int func(queue<int> que1, queue<int> que2, queue<int> que3) {
    //TODO
    int min_distance = 0x3f3f3f3f;
    while (!que1.empty() && !que2.empty() && !que3.empty()) {
        int min_1 = que1.front(), min_2 = que2.front(), min_3 = que3.front();
        int temp_min_distance = abs(min_1 - min_2) + abs(min_2 - min_3) + abs(min_1 - min_3);
        if (temp_min_distance < min_distance) {
            min_distance = temp_min_distance;
        }
        int most_min = min_num(min_1, min_2 , min_3);
        if (min_1 == most_min) que1.pop();
        if (min_2 == most_min) que2.pop();
        if (min_3 == most_min) que3.pop();
    }
    return min_distance;
}

int main() {
    int m, n, k, x;
    queue<int> que1, que2, que3;
    cin >> m >> n >> k;
    for (int i = 0; i < m; i++) {
        cin >> x;
        que1.push(x);
    }
    for (int i = 0; i < n; i++) {
        cin >> x;
        que2.push(x);
    }
    for (int i = 0; i < k; i++) {
        cin >> x;
        que3.push(x);
    }
    cout << func(que1, que2, que3) << endl;
    return 0;
}