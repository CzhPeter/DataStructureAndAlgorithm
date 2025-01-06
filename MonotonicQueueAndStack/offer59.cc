/*
请定义一个队列并实现函数 max_value 得到队列里的最大值，
要求函数 max_value, push_back 和 pop_front 的均摊时间复杂度都是 O(1)。
若队列为空，pop_front 和 max_value 需要返回 -1
*/

#include <iostream>
#include <deque>
#include <queue>
#include <vector>

using namespace std;

class MaxQueue {
public:
    queue<int> q;
    deque<int> mq;
    MaxQueue() {}

    int max_value() {
        if (q.empty()) return -1;
        return mq.front();
    }

    void push_back(int value) {
        q.push(value);
        while (!mq.empty() && mq.back() < value) {
            mq.pop_back();
        }
        mq.push_back(value);
        return;
    }

    int pop_front() {
        if (q.empty()) return -1;
        int val = q.front();
        q.pop();
        if (mq.front() == val) {
            mq.pop_front();
        }
        return val;
    }
};
