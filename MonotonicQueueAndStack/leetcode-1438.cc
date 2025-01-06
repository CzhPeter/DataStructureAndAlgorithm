/*
Given an array of integers nums and an integer limit, 
return the size of the longest non-empty subarray such that the absolute difference between any two elements of this subarray is less than or equal to limit.
Example 1:
Input: nums = [8,2,4,7], limit = 4
Output: 2 
Explanation: All subarrays are: 
[8] with maximum absolute diff |8-8| = 0 <= 4.
[8,2] with maximum absolute diff |8-2| = 6 > 4. 
[8,2,4] with maximum absolute diff |8-2| = 6 > 4.
[8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.
[2] with maximum absolute diff |2-2| = 0 <= 4.
[2,4] with maximum absolute diff |2-4| = 2 <= 4.
[2,4,7] with maximum absolute diff |2-7| = 5 > 4.
[4] with maximum absolute diff |4-4| = 0 <= 4.
[4,7] with maximum absolute diff |4-7| = 3 <= 4.
[7] with maximum absolute diff |7-7| = 0 <= 4. 
Therefore, the size of the longest subarray is 2.
*/

#include <iostream>
#include <vector>
#include <deque>
#include <stack>

using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        if (limit < 0) return 0;
        deque<int> min_q, max_q;
        int l = 0, ans = 1;
        min_q.push_back(0);
        max_q.push_back(0);
        for (int r = 1, n = nums.size(); r < n; ++r) {
            while (!min_q.empty() && nums[r] < nums[min_q.back()]) {
                min_q.pop_back();
            }
            min_q.push_back(r);
            while (!max_q.empty() && nums[r] > nums[max_q.back()]) {
                max_q.pop_back();
            }
            max_q.push_back(r);
            while (nums[max_q.front()] - nums[min_q.front()] > limit) {
                if (min_q.front() == l) min_q.pop_front();
                if (max_q.front() == l) max_q.pop_front();
                l += 1;
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};