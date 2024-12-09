/*
The median is the middle value in an ordered integer list. 
If the size of the list is even, there is no middle value, 
and the median is the mean of the two middle values.
Implement the MedianFinder class:
1. MedianFinder() 
initializes the MedianFinder object.
2. void addNum(int num) 
adds the integer num from the data stream to the data structure.
3. double findMedian() 
returns the median of all elements so far. 
Answers within 10-5 of the actual answer will be accepted.
Input
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
Output
[null, null, null, 1.5, null, 2.0]
*/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

class MedianFinder {
public:
    // 将数据从小到大排列并于中间隔开，前半段的最后一个元素为该段最大值，后半段第一个元素为该段最小值
    // 中位数即由这两个元素中产生或计算
    // 前后两半段都可以用堆来维护（对顶堆），前半段为大顶堆，后半段为小顶堆
    // 偶数个数n: 前后半段都为n / 2个元素
    // 奇数个数n: 前半段 n / 2 + 1，后半段n / 2个元素
    typedef pair<int, int> PII;
    int tot;
    set<PII> s1, s2; // s1存负值来模拟大顶堆
    MedianFinder() {
        tot = 0;
    }
    
    void addNum(int num) {
        if (s1.size() == 0 || num < -s1.begin()->first) {
            s1.insert(PII(-num, tot++));
        } else {
            s2.insert(PII(num, tot++));
        }
        int n1 = (s1.size() + s2.size() + 1) / 2; // 理论上第一个集合应该有的元素数量
        if (s1.size() == n1) return;
        // 调整两个堆的元素数量
        if (s1.size() < n1) {
            s1.insert(PII(-s2.begin()->first, s2.begin()->second));
            s2.erase(s2.begin());
        } else {
            s2.insert(PII(-s1.begin()->first, s1.begin()->second));
            s1.erase(s1.begin());
        }
    }
    
    double findMedian() {
        if ((s1.size() + s2.size()) % 2) {
            return -s1.begin()->first;
        }
        double a = -s1.begin()->first;
        double b = s2.begin()->first;
        return (a + b) / 2;
    }
};