/*
You are tasked to implement a class which, for a given integer k, 
maintains a stream of test scores and continuously returns the kth highest test score 
after a new score has been submitted. 
More specifically, we are looking for the kth highest score in the sorted list of all scores.
Implement the KthLargest class:
1. KthLargest(int k, int[] nums) 
Initializes the object with the integer k and the stream of test scores nums.
2. int add(int val) 
Adds a new test score val to the stream and returns the element representing the kth largest element in the pool of test scores so far.
Input:
["KthLargest", "add", "add", "add", "add", "add"]
[[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
Output: [null, 4, 5, 5, 8, 8]
*/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

class KthLargest {
public:
    // 第k大的值，相当于，前k个最大元素中的最小值，使用k个元素的小顶堆维护
    typedef pair<int, int> PII;
    int tot, k;
    set<PII> s;
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        for (auto x : nums) {
            add(x);
        }
        return;
    }
    
    int add(int val) {
        // 元素数量小于k个就直接插入
        if (s.size() < k) {
            s.insert(PII(val, tot++));
        } else { // 比堆顶元素大的才能插入堆
            if (s.begin()->first < val) {
                s.insert(PII(val, tot++));
            }
        }
        // 插入完堆的元素数量大于k的话，弹出堆顶元素
        if (s.size() > k) {
            s.erase(s.begin());
        }
        return s.begin()->first;
    }
};