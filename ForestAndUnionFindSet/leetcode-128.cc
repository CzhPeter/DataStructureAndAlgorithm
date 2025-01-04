/*
Given an unsorted array of integers nums, 
return the length of the longest consecutive elements sequence.
You must write an algorithm that runs in O(n) time.
Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. 
Therefore its length is 4.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    class UnionSet {
    public:
        UnionSet(int n) : fa(n + 1), size(n + 1) {
            for (int i = 0; i <= n; ++i) {
                fa[i] = i;
                size[i] = 1;         
            }
        }

        int find(int x) {
            return fa[x] = (fa[x] == x ? x : find(fa[x]));
        }

        int merge(int a, int b) {
            int aa = find(a), bb = find(b);
            if (aa == bb) return 0;
            fa[aa] = bb;
            size[bb] += size[aa];
            return 1;
        }

        vector<int> fa, size;
    };

    int longestConsecutive(vector<int>& nums) {
        int n = nums.size(), count = 0;
        unordered_map<int, int> h;
        UnionSet u(n);
        for (int i = 0; i < n; ++i) {
            int x = nums[i];
            if (h.find(x) != h.end()) continue;
            h[x] = (count++); // 给每个数字赋予一个并查集的节点编号
            // 对连续数字做并查集合并操作
            if (h.find(x + 1) != h.end()) {
                u.merge(h[x], h[x + 1]);
            }
            if (h.find(x - 1) != h.end()) {
                u.merge(h[x], h[x - 1]);
            }
        }
        // 找到最大集合
        int ans = 0;
        for (int i = 0; i < count; ++i) {
            ans = max(ans, u.size[i]);
        }
        return ans;
    }
};